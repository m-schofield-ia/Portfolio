#ifndef INCLUDE_H
#define INCLUDE_H

#include <PalmOS.h>
#include "Resources.h"

/* macros */
#define EVER ;;
#define CRID 'pmxX'
#define APPVER 1
#define LvlDenomMask 63
#define LvlAdvanced 64
#define LvlAdvancedShift 6
#define LvlMixed 128
#define LvlMixedShift 7

enum { PrfApplication=0, PrfSession };

typedef struct {
	UInt32 round;
	UInt32 score;
	UInt16 guesses;
	UInt16 mask;
	UInt16 numerator;
	UInt16 denominator;
	UInt16 whole;
	UInt16 wNum;
	UInt16 wDenom;
} Session;

typedef struct {
	FormType *oldForm;
	UInt16 oldId;
	FormActiveStateType state;
} FormSave;

/* AboutForm.c */
void About(void);

/* Preferences.c */
void Preferences(void);

/* Session.c */
void SssGet(void);
void SssNew(void);
void SssUpdate(UInt16);
void SssSet(void);
void SssDestroy(void);

/* UI.c */
void *UIFormGetObject(UInt16);
void UIFormPrologue(FormSave *, UInt16, FormEventHandlerType *);
Boolean UIFormEpilogue(FormSave *, void (*)(), UInt16);
void UIFieldFocus(UInt16);
Boolean UIFieldRefocus(UInt16 *, WChar);
Char *UIFieldGetText(UInt16);
void UIFieldSetText(UInt16, Char *);
void UIFieldClear(UInt16);
Boolean UIFieldScrollBarHandler(EventType *, UInt16, UInt16);
Boolean UIFieldScrollBarKeyHandler(EventType *, UInt16, UInt16);
void UIFieldUpdateScrollBar(UInt16, UInt16);
void UIFieldScrollLines(UInt16, Int16);
void UIFieldPageScroll(UInt16, UInt16, WinDirectionType);
void UIShowObject(UInt16);
void UIHideObject(UInt16);

/* Utils.c */
Boolean UtilsRomCheck(void);
Boolean UtilsGetPref(void *, UInt16, UInt16);
void UtilsSetPref(void *, UInt16, UInt16);
void UtilsReduce(UInt16 *, UInt16 *);

/* fGame.c */
Boolean fGameInit(void);
Boolean fGameEH(EventType *);

/* fMain.c */
Boolean fMainEH(EventType *);

/* Debug.c */
#if DEBUG==1
#define D(x) x
void DAlert(UInt8 *, ...);
#else
#define D(x) ;
#endif

#ifdef MAIN
	UInt16 mask[]={ 0xfffe, 0xfffd, 0xfffb, 0xfff7, 0xffef };
	UInt16 currentFormID, level;
	FormPtr currentForm;
	Session *session;
#else
	extern UInt16 mask[];
	extern UInt16 currentFormID, level;
	extern FormPtr currentForm;
	extern Session *session;
#endif

#endif
