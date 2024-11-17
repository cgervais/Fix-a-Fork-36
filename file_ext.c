/*
	Copyright Eric Helgeson, jcs 2023-2024.
*/

#include "file_ext.h"
#include <stdbool.h>

// Simple file ext checks as fallback.
static const struct {
	char *extension;
	OSType type;
	OSType creator;
} exttypes[] = {
	{ "1st", 'TEXT', 'ttxt' }, // Text Readme
	{ "669", '6669', 'SNPL' }, // 669 - MOD
	{ "8med", 'STrk', 'SCPL' }, // Amiga - OctaMed
	{ "8svx", '8SVX', 'SCPL' }, // Amiga - 8-bit
	{ "aif", 'AIFF', 'SCPL' }, // AIFF - Sound
	{ "aifc", 'AIFC', 'SCPL' }, // AIFF - Sound
	{ "aiff", 'AIFF', 'SCPL' }, // AIFF - Sound
	{ "al", 'ALAW', 'SCPL' }, // ALAW - Sound
	{ "ani", 'ANIi', 'GKON' }, // Animated - NeoChrome
	{ "apd", 'TEXT', 'ALD3' }, // Aldus - Printer
	{ "arc", 'mArc', 'SITx' }, // PC - ARChive
	{ "arj", 'BINA', 'DArj' }, // ARJ - Archive
	{ "arr", 'ARR ', 'GKON' }, // Amber - ARR
	{ "art", 'ART ', 'GKON' }, // First - Publisher
	{ "ascii", 'TEXT', 'ttxt' }, // ASCII - Text
	{ "asc", 'TEXT', 'ttxt' }, // ASCII - Text
	{ "asf", 'ASF_', 'Ms01' }, // Netshow - Player
	{ "asm", 'TEXT', 'ttxt' }, // Assembly - Source
	{ "asx", 'ASX_', 'Ms01' }, // Netshow - Player
	{ "a", 'TEXT', 'ttxt' }, // Assembly - Source
	{ "au", 'ULAW', 'TVOD' }, // Sun - Sound
	{ "avi", 'VfW ', 'TVOD' }, // AVI - Movie
	{ "bar", 'BARF', 'S691' }, // Unix - BAR
	{ "bas", 'TEXT', 'ttxt' }, // BASIC - Source
	{ "bat", 'TEXT', 'ttxt' }, // MS-DOS - Batch
	{ "bga", 'BMPp', 'ogle' }, // OS/2 - Bitmap
	{ "bib", 'TEXT', 'ttxt' }, // BibTex - Bibliography
	{ "binary", 'BINA', 'hDmp' }, // Untyped - Binary
	{ "bin", 'BINA', 'SITx' }, // MacBinary - StuffIt
	{ "bld", 'BLD ', 'GKON' }, // BLD - GraphicConverter
	{ "bmp", 'BMPp', 'ogle' }, // Windows - Bitmap
	{ "boo", 'TEXT', 'ttxt' }, // BOO - encoded
	{ "bst", 'TEXT', 'ttxt' }, // BibTex - Style
	{ "bum", '.bMp', 'GKON' }, // QuickTime - Importer(QuickDraw)
	{ "bw", 'SGI ', 'GKON' }, // SGI - Image
	{ "bz", 'Bzp2', 'SITx' }, // BZip2 - StuffIt
	{ "cel", 'CEL ', 'GKON' }, // KISS - CEL
	{ "cgm", 'CGMm', 'GKON' }, // Computer - Graphics
	{ "class", 'Clss', 'CWIE' }, // Java - Class
	{ "clp", 'CLPp', 'GKON' }, // Windows - Clipboard
	{ "cmd", 'TEXT', 'ttxt' }, // OS/2 - Batch
	{ "com", 'PCFA', 'SWIN' }, // MS-DOS - Executable
	{ "cpp", 'TEXT', 'CWIE' }, // C++ - Source
	{ "cp", 'TEXT', 'CWIE' }, // C++ - Source
	{ "cpt", 'PACT', 'SITx' }, // Compact - Pro
	{ "csv", 'TEXT', 'XCEL' }, // Comma - Separated
	{ "ct", '..CT', 'GKON' }, // Scitex-CT - GraphicConverter
	{ "c", 'TEXT', 'KAHL' }, // C - Source
	{ "cur", 'CUR ', 'GKON' }, // Windows - Cursor
	{ "cut", 'Halo', 'GKON' }, // Dr - Halo
	{ "cvs", 'drw2', 'DAD2' }, // Canvas - Drawing
	{ "cwj", 'CWSS', 'cwkj' }, // ClarisWorks - Document
	{ "dat", 'TCLl', 'GKON' }, // TCL - image
	{ "dbf", 'COMP', 'FOX+' }, // DBase - Document
	{ "dcx", 'DCXx', 'GKON' }, // Some - PCX
	{ "dif", 'TEXT', 'XCEL' }, // Data - Interchange
	{ "diz", 'TEXT', 'R*Ch' }, // BBS - Descriptive
	{ "dl", 'DL  ', 'AnVw' }, // DL - Animation
	{ "dll", 'PCFL', 'SWIN' }, // Windows - DLL
	{ "doc", 'WDBN', 'MSWD' }, // Word - Document
	{ "dot", 'sDBN', 'MSWD' }, // Word - for
	{ "dsk", 'dimg', 'dCpy' }, // Apple - DiskCopy
	{ "dvi", 'ODVI', 'xdvi' }, // TeX - DVI
	{ "dwt", 'TEXT', 'DmWr' }, // Dreamweaver - Template
	{ "dxf", 'TEXT', 'SWVL' }, // AutoCAD - 3D
	{ "eps", 'EPSF', 'vgrd' }, // Postscript - LaserWriter
	{ "epsf", 'EPSF', 'vgrd' }, // Postscript - LaserWriter
	{ "etx", 'TEXT', 'ezVu' }, // SEText - Easy
	{ "evy", 'EVYD', 'ENVY' }, // Envoy - Document
	{ "exe", 'PCFA', 'SWIN' }, // MS-DOS - Executable
	{ "faq", 'TEXT', 'ttxt' }, // ASCII - Text
	{ "fit", 'FITS', 'GKON' }, // Flexible - Image
	{ "fla", 'SPA ', 'MFL2' }, // Flash - source
	{ "flc", 'FLI ', 'TVOD' }, // FLIC - Animation
	{ "fli", 'FLI ', 'TVOD' }, // FLI - Animation
	{ "fm", 'FMPR', 'FMPR' }, // FileMaker - Pro
	{ "for", 'TEXT', 'MPS ' }, // Fortran - Source
	{ "fts", 'FITS', 'GKON' }, // Flexible - Image
	{ "gem", 'GEM-', 'GKON' }, // GEM - Metafile
	{ "gif", 'GIFf', 'ogle' }, // GIF - Picture
	{ "gl", 'GL  ', 'AnVw' }, // GL - Animation
	{ "grp", 'GRPp', 'GKON' }, // GRP - Image
	{ "gz", 'SIT!', 'SITx' }, // Gnu - ZIP
	{ "hcom", 'FSSD', 'SCPL' }, // SoundEdit - Sound
	{ "hpgl", 'HPGL', 'GKON' }, // HP - GL/2
	{ "hpp", 'TEXT', 'CWIE' }, // C - Include
	{ "hp", 'TEXT', 'CWIE' }, // C - Include
	{ "hqx", 'TEXT', 'SITx' }, // BinHex - StuffIt
	{ "hr", 'TR80', 'GKON' }, // TSR-80 - HR
	{ "h", 'TEXT', 'KAHL' }, // C - Include
	{ "html", 'TEXT', 'MOSS' }, // HyperText - Netscape
	{ "htm", 'TEXT', 'MOSS' }, // HyperText - Netscape
	{ "i3", 'TEXT', 'R*ch' }, // Modula - 3
	{ "ic1", 'IMAG', 'GKON' }, // Atari - Image
	{ "ic2", 'IMAG', 'GKON' }, // Atari - Image
	{ "ic3", 'IMAG', 'GKON' }, // Atari - Image
	{ "icn", 'ICO ', 'GKON' }, // Windows - Icon
	{ "ico", 'ICO ', 'GKON' }, // Windows - Icon
	{ "ief", 'IEF ', 'GKON' }, // IEF - image
	{ "iff", 'ILBM', 'GKON' }, // Amiga - IFF
	{ "ilbm", 'ILBM', 'GKON' }, // Amiga - ILBM
	{ "image", 'dImg', 'ddsk' }, // Apple - DiskCopy
	{ "img", 'dImg', 'ddsk' }, // Apple - DiskCopy
	{ "ini", 'TEXT', 'ttxt' }, // Windows - INI
	{ "iso", 'rodh', 'ddsk' }, // Apple - ISO
	{ "iss", 'ISS ', 'GKON' }, // ISS - GraphicConverter
	{ "java", 'TEXT', 'CWIE' }, // Java - Source
	{ "jfif", 'JPEG', 'ogle' }, // JFIF - Image
	{ "jif", 'JIFf', 'GKON' }, // JIF99a - GraphicConverter
	{ "jpeg", 'JPEG', 'ogle' }, // JPEG - Picture
	{ "jpe", 'JPEG', 'ogle' }, // JPEG - Picture
	{ "jpg", 'JPEG', 'ogle' }, // JPEG - Picture
	{ "latex", 'TEXT', 'OTEX' }, // Latex - OzTex
	{ "lbm", 'ILBM', 'GKON' }, // Amiga - IFF
	{ "lha", 'LHA ', 'SITx' }, // LHArc - Archive
	{ "lwf", 'lwfF', 'GKON' }, // LuraWave(LWF) - GraphicConverter
	{ "lzh", 'LHA ', 'SITx' }, // LHArc - Archive
	{ "m1a", 'MPEG', 'TVOD' }, // MPEG-1 - audiostream
	{ "m1s", 'MPEG', 'TVOD' }, // MPEG-1 - systemstream
	{ "m1v", 'M1V ', 'TVOD' }, // MPEG-1 - IPB
	{ "m2", 'TEXT', 'R*ch' }, // Modula - 2
	{ "m2v", 'MPG2', 'MPG2' }, // MPEG-2 - IPB
	{ "m3", 'TEXT', 'R*ch' }, // Modula - 3
	{ "mac", 'PICT', 'ogle' }, // PICT - Picture
	{ "mak", 'TEXT', 'R*ch' }, // Makefile - BBEdit
	{ "mbm", 'MBM ', 'GKON' }, // PSION - 5(MBM)
	{ "mcw", 'WDBN', 'MSWD' }, // Mac - Word
	{ "med", 'STrk', 'SCPL' }, // Amiga - MED
	{ "me", 'TEXT', 'ttxt' }, // Text - Readme
	{ "mf", 'TEXT', '*MF*' }, // Metafont - Metafont
	{ "midi", 'Midi', 'TVOD' }, // MIDI - Music
	{ "mid", 'Midi', 'TVOD' }, // MIDI - Music
	{ "mif", 'TEXT', 'Fram' }, // FrameMaker - MIF
	{ "mime", 'TEXT', 'SITx' }, // MIME - Message
	{ "ml", 'TEXT', 'R*ch' }, // ML - Source
	{ "mod", 'STrk', 'SCPL' }, // MOD - Music
	{ "mol", 'TEXT', 'RSML' }, // MDL - Molfile
	{ "moov", 'MooV', 'TVOD' }, // QuickTime - Movie
	{ "mov", 'MooV', 'TVOD' }, // QuickTime - Movie
	{ "mp2", 'MPEG', 'TVOD' }, // MPEG-1 - audiostream
	{ "mp3", 'MPG3', 'TVOD' }, // MPEG-3 - audiostream
	{ "mpa", 'MPEG', 'TVOD' }, // MPEG-1 - audiostream
	{ "mpeg", 'MPEG', 'TVOD' }, // MPEG - Movie
	{ "mpe", 'MPEG', 'TVOD' }, // MPEG - Movie
	{ "mpg", 'MPEG', 'TVOD' }, // MPEG - Movie
	{ "msp", 'MSPp', 'GKON' }, // Microsoft - Paint
	{ "mtm", 'MTM ', 'SNPL' }, // MultiMOD - Music
	{ "mwii", 'MW2D', 'MWII' }, // MacWrite - Document
	{ "mw", 'MW2D', 'MWII' }, // MacWrite - Document
	{ "neo", 'NeoC', 'GKON' }, // Atari - NeoChrome
	{ "nfo", 'TEXT', 'ttxt' }, // Info - Text
	{ "ngg", 'NGGC', 'GKON' }, // Mobile - Phone(Nokia)Format
	{ "nol", 'NOL ', 'GKON' }, // Mobile - Phone(Nokia)Format
	{ "nst", 'STrk', 'SCPL' }, // MOD - Music
	{ "obj", 'PCFL', 'SWIN' }, // Object - (DOS/Windows)
	{ "oda", 'ODIF', 'ODA ' }, // ODA - Document
	{ "okt", 'OKTA', 'SCPL' }, // Oktalyser - MOD
	{ "out", 'BINA', 'hDmp' }, // Output - File
	{ "ovl", 'PCFL', 'SWIN' }, // Overlay - (DOS/Windows)
	{ "pac", 'STAD', 'GKON' }, // Atari - STAD
	{ "pal", '8BCT', '8BIM' }, // Color - Table
	{ "pas", 'TEXT', 'CWIE' }, // Pascal - Source
	{ "pbm", 'PPGM', 'GKON' }, // Portable - Bitmap
	{ "pc1", 'Dega', 'GKON' }, // Atari - Degas
	{ "pc2", 'Dega', 'GKON' }, // Atari - Degas
	{ "pc3", 'Dega', 'GKON' }, // Atari - Degas
	{ "pcs", 'PICS', 'GKON' }, // Animated - PICTs
	{ "pct", 'PICT', 'ogle' }, // PICT - Picture
	{ "pcx", 'PCXx', 'GKON' }, // PC - PaintBrush
	{ "pdb", 'TEXT', 'RSML' }, // Brookhaven - PDB
	{ "pdf", 'PDF ', 'CARO' }, // Portable - Document
	{ "pdx", 'TEXT', 'ALD5' }, // Printer - Description
	{ "pf", 'CSIT', 'SITx' }, // Private - File
	{ "pgc", 'PGCF', 'GKON' }, // PGC/PGF - Atari
	{ "pgm", 'PPGM', 'GKON' }, // Portable - Graymap
	{ "pi1", 'Dega', 'GKON' }, // Atari - Degas
	{ "pi2", 'Dega', 'GKON' }, // Atari - Degas
	{ "pi3", 'Dega', 'GKON' }, // Atari - Degas
	{ "pic", 'PICT', 'ogle' }, // PICT - Picture
	{ "pics", 'PICS', 'GKON' }, // PICS-PICT - Sequence
	{ "pict", 'PICT', 'ogle' }, // PICT - Picture
	{ "pit", 'PIT ', 'SITx' }, // PackIt - Archive
	{ "pkg", 'HBSF', 'SITx' }, // AppleLink - Package
	{ "pl", 'TEXT', 'McPL' }, // Perl - Source
	{ "plt", 'HPGL', 'GKON' }, // HP - GL/2
	{ "pm3", 'ALB3', 'ALD3' }, // PageMaker - 3
	{ "pm4", 'ALB4', 'ALD4' }, // PageMaker - 4
	{ "pm5", 'ALB5', 'ALD5' }, // PageMaker - 5
	{ "pm", 'PMpm', 'GKON' }, // Bitmap - from
	{ "png", 'PNG ', 'ogle' }, // Portable - Network
	{ "pntg", 'PNTG', 'ogle' }, // Macintosh - Painting
	{ "ppd", 'TEXT', 'ALD5' }, // Printer - Description
	{ "ppm", 'PPGM', 'GKON' }, // Portable - Pixmap
	{ "prn", 'TEXT', 'R*ch' }, // Printer - Output
	{ "psd", '8BPS', '8BIM' }, // PhotoShop - Document
	{ "ps", 'TEXT', 'vgrd' }, // PostScript - LaserWriter
	{ "pt4", 'ALT4', 'ALD4' }, // PageMaker - 4
	{ "pt5", 'ALT5', 'ALD5' }, // PageMaker - 5
	{ "p", 'TEXT', 'CWIE' }, // Pascal - Source
	{ "pxr", 'PXR ', '8BIM' }, // Pixar - Image
	{ "qdv", 'QDVf', 'GKON' }, // QDV - image
	{ "qt", 'MooV', 'TVOD' }, // QuickTime - Movie
	{ "qxd", 'XDOC', 'XPR3' }, // QuarkXpress - Document
	{ "qxt", 'XTMP', 'XPR3' }, // QuarkXpress - Template
	{ "raw", 'rodh', 'ddsk' }, // Apple - raw
	{ "readme", 'TEXT', 'ttxt' }, // Text - Readme
	{ "rgba", 'SGI ', 'GKON' }, // SGI - Image
	{ "rgb", 'SGI ', 'GKON' }, // SGI - Image
	{ "rib", 'TEXT', 'RINI' }, // Renderman - 3D
	{ "rif", 'RIFF', 'GKON' }, // RIFF - Graphic
	{ "rle", 'RLE ', 'GKON' }, // RLE - image
	{ "rme", 'TEXT', 'ttxt' }, // Text - Readme
	{ "rpl", 'FRL!', 'REP!' }, // Replica - Document
	{ "rsc", 'rsrc', 'RSED' }, // Resource - File
	{ "rsrc", 'rsrc', 'RSED' }, // Resource - File
	{ "rtf", 'TEXT', 'MSWD' }, // Rich - Text
	{ "rtx", 'TEXT', 'R*ch' }, // Rich - Text
	{ "s3m", 'S3M ', 'SNPL' }, // ScreamTracker - 3
	{ "scc", 'MSX ', 'GKON' }, // MSX - pitcure
	{ "scg", 'RIX3', 'GKON' }, // ColoRIX - GraphicConverter
	{ "sci", 'RIX3', 'GKON' }, // ColoRIX - GraphicConverter
	{ "scp", 'RIX3', 'GKON' }, // ColoRIX - GraphicConverter
	{ "scr", 'RIX3', 'GKON' }, // ColoRIX - GraphicConverter
	{ "scu", 'RIX3', 'GKON' }, // ColoRIX - GraphicConverter
	{ "sea", 'APPL', '????' }, // Self-Extracting - Archive
	{ "sf", 'IRCM', 'SDHK' }, // IRCAM - Sound
	{ "sgi", '.SGI', 'ogle' }, // SGI - Image
	{ "shar", 'TEXT', 'UnSh' }, // Unix - Shell
	{ "sha", 'TEXT', 'UnSh' }, // Unix - Shell
	{ "shp", 'SHPp', 'GKON' }, // Printmaster - Icon
	{ "sithqx", 'TEXT', 'SITx' }, // BinHexed - StuffIt
	{ "sit", 'SIT!', 'SITx' }, // StuffIt - 1.5.1
	{ "six", 'SIXE', 'GKON' }, // SIXEL - image
	{ "slk", 'TEXT', 'XCEL' }, // SYLK - Spreadsheet
	{ "snd", 'BINA', 'SCPL' }, // Sound - of
	{ "spc", 'Spec', 'GKON' }, // Atari - Spectrum
	{ "sr", 'SUNn', 'GKON' }, // Sun - Raster
	{ "sty", 'TEXT', '*TEX' }, // TeX - Style
	{ "sun", 'SUNn', 'GKON' }, // Sun - Raster
	{ "sup", 'SCRN', 'GKON' }, // StartupScreen - GraphicConverter
	{ "svx", '8SVX', 'SCPL' }, // Amiga - IFF
	{ "swf", 'SWFL', 'SWF2' }, // Flash - Macromedia
	{ "syk", 'TEXT', 'XCEL' }, // SYLK - Spreadsheet
	{ "sylk", 'TEXT', 'XCEL' }, // SYLK - Spreadsheet
	{ "targa", 'TPIC', 'GKON' }, // Truevision - Image
	{ "tar", 'TARF', 'SITx' }, // Unix - Tape
	{ "taz", 'ZIVU', 'SITx' }, // Compressed - Tape
	{ "texinfo", 'TEXT', 'OTEX' }, // TeX - Document
	{ "texi", 'TEXT', 'OTEX' }, // TeX - Document
	{ "tex", 'TEXT', 'OTEX' }, // TeX - Document
	{ "text", 'TEXT', 'ttxt' }, // ASCII - Text
	{ "tga", 'TPIC', 'GKON' }, // Truevision - Image
	{ "tgz", 'Gzip', 'SITx' }, // Gnu - ZIPed
	{ "tiff", 'TIFF', 'ogle' }, // TIFF - Picture
	{ "tif", 'TIFF', 'ogle' }, // TIFF - Picture
	{ "tny", 'TINY', 'GKON' }, // Atari - TINY
	{ "toast", 'CDr3', 'GImg' }, // CD - Image
	{ "tsv", 'TEXT', 'XCEL' }, // Tab - Separated
	{ "tx8", 'TEXT', 'ttxt' }, // 8-bit - ASCII
	{ "txt", 'TEXT', 'ttxt' }, // ASCII - Text
	{ "ul", 'ULAW', 'TVOD' }, // Mu-Law - Sound
	{ "url", 'AURL', 'Arch' }, // URL - Bookmark
	{ "uue", 'TEXT', 'SITx' }, // UUEncode - StuffIt
	{ "uu", 'TEXT', 'SITx' }, // UUEncode - StuffIt
	{ "vff", 'VFFf', 'GKON' }, // DESR - VFF
	{ "vga", 'BMPp', 'ogle' }, // OS/2 - Bitmap
	{ "voc", 'VOC ', 'SCPL' }, // VOC - Sound
	{ "vpb", 'VPB ', 'GKON' }, // VPB - QUANTEL
	{ "w51", '.WP5', 'WPC2' }, // WordPerfect - PC
	{ "wav", 'WAVE', 'TVOD' }, // Windows - WAV
	{ "wbmp", 'WBMP', 'GKON' }, // WBMP - GraphicConverter
	{ "wk1", 'XLBN', 'XCEL' }, // Lotus - Spreadsheet
	{ "wks", 'XLBN', 'XCEL' }, // Lotus - Spreadsheet
	{ "wmf", 'WMF ', 'GKON' }, // Windows - Metafile
	{ "wp4", '.WP4', 'WPC2' }, // WordPerfect - PC
	{ "wp5", '.WP5', 'WPC2' }, // WordPerfect - PC
	{ "wp6", '.WP6', 'WPC2' }, // WordPerfect - PC
	{ "wpg", 'WPGf', 'GKON' }, // WordPerfect - Graphic
	{ "wpm", 'WPD1', 'WPC2' }, // WordPerfect - Mac
	{ "wp", '.WP5', 'WPC2' }, // WordPerfect - PC
	{ "wri", 'WDBN', 'MSWD' }, // MS - Write/Windows
	{ "wve", 'BINA', 'SCPL' }, // PSION - sound
	{ "x10", 'XWDd', 'GKON' }, // X-Windows - Dump
	{ "x11", 'XWDd', 'GKON' }, // X-Windows - Dump
	{ "xbm", 'XBM ', 'GKON' }, // X-Windows - Bitmap
	{ "x-face", 'TEXT', 'GKON' }, // X-Face - GraphicConverter
	{ "xlc", 'XLC ', 'XCEL' }, // Excel - Chart
	{ "xlm", 'XLM ', 'XCEL' }, // Excel - Macro
	{ "xls", 'XLS ', 'XCEL' }, // Excel - Spreadsheet
	{ "xlw", 'XLW ', 'XCEL' }, // Excel - Workspace
	{ "xl", 'XLS ', 'XCEL' }, // Excel - Spreadsheet
	{ "xm", 'XM  ', 'SNPL' }, // FastTracker - MOD
	{ "xpm", 'XPM ', 'GKON' }, // X-Windows - Pixmap
	{ "xwd", 'XWDd', 'GKON' }, // X-Windows - Dump
	{ "zip", 'ZIP ', 'SITx' }, // PC - ZIP
	{ "zoo", 'Zoo ', 'Booz' }, // Zoo - Archive
	{ "Z", 'ZIVU', 'SITx' }, // Unix - Compress
};

Boolean CheckFileExt(const char *ext, OSType *type, OSType *creator)
{
	short n, j;

	for (n = 0; n < (sizeof(exttypes) / sizeof(exttypes[0])); n++) {
		for (j = 0; ; j++) {
			if (exttypes[n].extension[j] != ext[j])
				break;
			if (exttypes[n].extension[j] == '\0' && ext[j] == '\0') {
				*type = exttypes[n].type;
				*creator = exttypes[n].creator;
				return true;
			}
		}
	}
	return false;
}