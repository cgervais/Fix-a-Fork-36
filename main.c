/*
	Copyright Eric Helgeson 2023-2024.
*/

#include "main.h"
#include "file_ext.h"
#include <Script.h>

// Globals
OSType gType;
OSType gCreator;
long gHasAppleEvents;

// Change the modification date on the parent folder so the 
// Finder notices a change.
OSErr TouchFolder(short vRefNum, long parID)
{
	CInfoPBRec rec;
	Str63 name; 
	short err;
	
	rec.hFileInfo.ioNamePtr = name;
	name[0]=0;
	rec.hFileInfo.ioVRefNum = vRefNum;
	rec.hFileInfo.ioDirID = parID;
	rec.hFileInfo.ioFDirIndex = -1;
	rec.hFileInfo.ioFVersNum = 0;
	err = PBGetCatInfoSync(&rec);
	if(err)
		return err;
	GetDateTime(&rec.dirInfo.ioDrMdDat);
	
	rec.hFileInfo.ioVRefNum = vRefNum;
	rec.hFileInfo.ioDirID = parID;
	rec.hFileInfo.ioFDirIndex = -1;
	rec.hFileInfo.ioFVersNum = 0;
	rec.hFileInfo.ioNamePtr[0] = 0;
	err = PBSetCatInfoSync(&rec);
	return err;
}

pascal OSErr DoOpenDoc(AppleEvent *event, AppleEvent *reply, long handlerRefcon)
{
	FSSpec fss;
	AEDescList docList;
	OSErr err = noErr;
	long index, itemsInList;
	Size actualSize;
	AEKeyword keywd;
	DescType returnedType;
	short fRefNum = 0;
	
	err = AEGetParamDesc(event, keyDirectObject, typeAEList, &docList);
	if(err != noErr) return err;
	err = AECountItems(&docList, &itemsInList);
	if(err != noErr) return err;
	
	for(index = 1; index <= itemsInList; index++)
	{
		err = AEGetNthPtr(&docList, index, typeFSS, &keywd, &returnedType, (Ptr)&fss, sizeof(fss), &actualSize);
		if(err) return err;

		err = FSpOpenDF(&fss, fsRdPerm, &fRefNum);
		if(err) return err;
		
		err = openFile(fss.name, fRefNum, fss.vRefNum, fss.parID);
		if(err) 
			return err;
		else
			gHandledByDnD = true;
	}
	AEDisposeDesc(&docList);
	return noErr;
}

void InstallEventHandlers()
{
	EventRecord event;
	OSErr err = 0;
	short i = 0;
	
	if(Gestalt(gestaltAppleEventsAttr, &gHasAppleEvents) == noErr)
	{
		AEInstallEventHandler(kCoreEventClass, kAEOpenDocuments, NewAEEventHandlerUPP(&DoOpenDoc), 0L, false);
	} else {
		return;
	}
	do {
		WaitNextEvent(highLevelEventMask, &event, 30, 0);
		i = i+1;
	} while(event.what != kHighLevelEvent && i < 5);
	if(event.what == kHighLevelEvent)
		AEProcessAppleEvent(&event);
}

OSErr MyGetWDInfo(short wdRefNum, short *vRefNum, long *dirID, long *procID)
{
	OSErr result;
	WDPBRec wdPB;
	wdPB.ioVRefNum = wdRefNum;
	wdPB.ioWDIndex = 0;
	wdPB.ioNamePtr = nil;
	result = PBGetWDInfoSync(&wdPB);
	*vRefNum = wdPB.ioWDVRefNum;
	*dirID = wdPB.ioWDDirID;
	*procID = wdPB.ioWDProcID;
	return result;
}

void OpenFileDialog()
{
	long dirID = 0, procID = 0;
	short volRefNum = 0;
	SFReply tr = {0};
	short fRefNum = 0;
	
	Point where;
	where.h = 100;
	where.v = 50;

	do {
		SFGetFile(where, nil, nil, -1, nil, nil, &tr);
		if(tr.good)
		{
			MyGetWDInfo(tr.vRefNum, &volRefNum, &dirID, &procID);
			HOpen(tr.vRefNum, dirID, tr.fName, fsRdPerm, &fRefNum);
			openFile(tr.fName, fRefNum, volRefNum, dirID);
		}
	} while(tr.good);
}

OSErr openFile(unsigned char *fName, short fRefNum, short vRefNum, long dirID)
{
	OSErr err = noErr;
	Str255 errString;
	long count = BUF_SIZE;
	FInfo fi = {0};
	Boolean found = false;
	char ext[5] = {0};
	short i = 0, j = 0;

	err = FSRead(fRefNum, &count, gBuf);
	// eofErr == partial read, probably small file, ok to continue.
	if(err && err != eofErr) return err;
	// Check for magic in first 1024 bytes
	if(isBinHex4())
		found = true;
	else if(isSit5())
		found = true;
	else if(isSit15())
		found = true;
	else if(isBinSit())
		found = true;
	else if(isDsk4())
		found = true;
	else if(isZip())
		found = true;
	else if(isMar())
		found = true;
	else if(isCpt())
		found = true;
		
	// Checks @ 1024
	if(!found && count >= 2048)
	{
		SetFPos(fRefNum, fsFromStart, 1024);
		FSRead(fRefNum, &count, gBuf);

		if(isDsk_1024())
			found = true;
	}
	
	if(!found)
	{
		for(i = fName[0]; i > 0; i--)
			if(fName[i] == '.')
				break;
		if(i != fName[0] && (fName[0] - i) <= 5) // There is an extension
		{
			i = i + 1; // increment to avoid '.'
			// Parse file extension
			for(; i <= fName[0]; i++)
				ext[j++] = fName[i];
			LowerText(ext, StringLen(ext));
			found = CheckFileExt(ext, &gType, &gCreator);
		}
	}
		
	if(found)
	{
		if(gCreator != 0 && gType != 0)
		{
			err = HGetFInfo(vRefNum, dirID, fName, &fi);
			if(err) return err;
			fi.fdType = gType;
			fi.fdCreator = gCreator;
			err = HSetFInfo(vRefNum, dirID, fName, &fi);

			if(err)
			{
				NumToString(err, errString);
				ParamText("\pCould't set type/creator for ", fName, "\p err: ", errString);
				StopAlert(128, nil);
			}
		}
		// else unkown type/creator
	} else {
		ParamText("\pCould't determine type/creator for ", fName, "\p", "\p");
		StopAlert(128, nil);
	}

	TouchFolder(vRefNum, dirID);
	return FSClose(fRefNum);
}

void main()
{
	MaxApplZone();
	InitGraf(&qd.thePort);
	InitFonts();
	InitWindows();
	InitMenus();
	TEInit();
	InitDialogs(nil);
	InitCursor();

	FlushEvents(everyEvent, 0);
	InstallEventHandlers();
	if(!gHandledByDnD)
		OpenFileDialog();
	return;
}
// TODO: Move to own file.

Boolean isBinHex4()
{
	// FixMe: Magic can be any line in the first 8k of the file.
	return magicCheck("BinHex 4.0", 10, 34, 'BINA', 'SITx');
}

Boolean isSit15()
{
	short stuffitVersion = 0;
	if(magicCheck("SIT!", 4, 0, 'SIT!', 'SIT!'))
	{
		gType = 0;
		gCreator = 0;
		// 0x01 for 1.5.x, 0x02 for 1.6-4.5
		stuffitVersion = gBuf[14];
		return (stuffitVersion == 0x01 || stuffitVersion == 0x02) && magicCheck("rLau", 4, 10, 'SIT!', 'SIT!');
	}
	return false;
}

Boolean isSit5()
{
	short stuffitVersion = gBuf[82]; // 0x05
	return (stuffitVersion == 0x05 && magicCheck("StuffIt (c)1997", 15, 0, 'SITD', 'SIT!'));
}

Boolean isBinSit()
{
	short stuffitVersion = 0;
	if(magicCheck("SIT!", 4, 0 + 128, 'SIT!', 'SIT!'))
	{
		gType = 0;
		gCreator = 0;
		// 0x01 for 1.5.x, 0x02 for 1.6-4.5
		stuffitVersion = gBuf[14 + 128];
		return (stuffitVersion == 0x01 || stuffitVersion == 0x02) && magicCheck("rLau", 4, 10 + 128, 'BINA', 'SITx');
	}
	return false;
}

Boolean isDsk4()
{
	char magic[] = "\1\0";
	return  magicCheck(magic, 2, 52, 'dImg', 'dCpy');
}
// Disk Copy 6
Boolean isDsk_1024()
{
	return  magicCheck("BD", 2, 0, 'DDim', 'ddsk');
}

// Very loose check, do last.
Boolean isCpt()
{
	char magic[] = "\1\1";
	return  magicCheck(magic, 2, 0, 'PACT', 'CPCT');
}

Boolean isMar()
{
	return  magicCheck("MAR", 3, 0, 'MARf', 'MARc');
}

Boolean isZip()
{
	return  magicCheck("PK", 2, 0, 'ZIP ', 'IZip');
}

short StringLen(const char *str)
{
	const char *s;
	for (s  = str; *s; ++s);
	return (s-str);
}

Boolean StringCompare(const char *lhs, const char *rhs)
{
	short i = 0;
	short len = StringLen(lhs);
	if(len != StringLen(rhs)) return false;
	
	for(i = 0; i < len; i++)
		if(lhs[i] != rhs[i])
			return false;
	return true;
}

Boolean magicCheck(char *magic, short len, short offset, OSType type, OSType creator)
{
	short i;
	for(i = 0; i < len; i++)
		if(gBuf[offset+i] != magic[i])
			return false;
	gType = type;
	gCreator = creator;
	return true;
}