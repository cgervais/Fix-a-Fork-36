/*
	Copyright Eric Helgeson 2023-2024.
*/
#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdbool.h>
#include <Files.h>
#include <StandardFile.h>
#include <Events.h>
#include <AppleEvents.h>
#include <Gestalt.h>
#include <Dialogs.h>
#include <Types.h>
#include <Strings.h>

#define BUF_SIZE 1024

// Globals
Byte gBuf[BUF_SIZE] = {0};
Boolean gHandledByDnD = false;

OSErr openFile(unsigned char *fName, short fRefNum, short vRefNum, long dirID);
pascal OSErr DoOpenDoc(AppleEvent *event, AppleEvent *reply, long handlerRefcon);

// checks
Boolean StringCompare(const char *lhs, const char *rhs);
short StringLen(const char *str);
Boolean magicCheck(char *magic, short len, short offset, OSType type, OSType creator);
Boolean isBinHex4();
Boolean isSit5();
Boolean isSit15();
Boolean isBinSit();
Boolean isDsk4();
Boolean isZip();
Boolean isMar();
Boolean isCpt();
Boolean isDsk_1024();
//Boolean CheckFileExt(const char *ext);
// short strlen(const char *str);
#endif