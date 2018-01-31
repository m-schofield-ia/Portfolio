/*
 * UI.c
 */
#include "Include.h"

/*
 * UIObjectGet
 *
 * Return pointer to form object given by id.
 *
 *  -> id		Object ID.
 *
 * Returns pointer or NULL (not found).
 */
void *
UIObjectGet(UInt16 id)
{
	return FrmGetObjectPtr(currentForm, FrmGetObjectIndex(currentForm, id));
}

/*
 * UIObjectShow
 *
 * Show an object in the current form.
 *
 *  -> id	Object ID.
 */
void
UIObjectShow(UInt16 id)
{
	FrmShowObject(currentForm, FrmGetObjectIndex(currentForm, id));
}

/*
 * UIFormPrologue
 *
 * Standard form start for Modal forms.
 *
 *  -> frm		Form object.
 *  -> id		ID of new form.
 *  -> eh		Event handler (NULL means no event handler).
 */
void
UIFormPrologue(FormSave *frm, UInt16 id, FormEventHandlerType *eh)
{
	frm->oldForm=currentForm;
	frm->oldId=currentFormID;
	FrmSaveActiveState(&frm->state);

	currentFormID=id;
	currentForm=FrmInitForm(id);
	ErrFatalDisplayIf(currentForm==NULL, "(UIFormPrologue) Cannot initialize form.");

	if (eh)
		FrmSetEventHandler(currentForm, eh);

	FrmSetActiveForm(currentForm);
	FrmDrawForm(currentForm);
}

/*
 * UIFormEpilogue
 *
 * Standard form for showing and ending Modal forms.
 *
 *  -> frm		Form object.
 *  -> hook		Hook - stuff to do after returning to previous form.
 *  -> falseButton	ID of button generating 'false' event (cancel).
 *
 *  Returns true or false (depending on which button was pressed).
 */
Boolean
UIFormEpilogue(FormSave *frm, void (*hook)(), UInt16 falseButton)
{
	UInt16 button;

	button=FrmDoDialog(currentForm);
	currentForm=frm->oldForm;
	FrmReturnToForm(frm->oldId);
	FrmRestoreActiveState(&frm->state);

	if (hook)
		hook();

	FrmDrawForm(currentForm);
	FrmUpdateForm(frm->oldId, frmRedrawUpdateCode);

	if (button==falseButton)
		return false;

	return true;
}

/*
 * UIFieldFocus
 *
 * Bring this field to Focus.
 *
 *   -> id		Field id in current form.
 */
void
UIFieldFocus(UInt16 id)
{
	FrmSetFocus(currentForm, FrmGetObjectIndex(currentForm, id));
}

/*
 * UIFieldGetText
 *
 * Get text field pointer.
 *
 *  -> id		Field id in current form.
 *
 * Returns whatever pointer is in the field.  Beware! Can be NULL!
 */
Char *
UIFieldGetText(UInt16 id)
{
	return FldGetTextPtr(UIObjectGet(id));
}

/*
 * UIFieldSetText
 *
 * Update field with copy of buffer.  Any previous text is discarded.
 *
 *  -> id		Field id in current form.
 *  -> buffer		Buffer to get text from.
 */
void
UIFieldSetText(UInt16 id, Char *buffer)
{
	FieldType *fld=UIObjectGet(id);
	UInt16 tLen=StrLen(buffer), max;
	MemHandle mh, oldH;
	Char *tp;

	if ((max=FldGetMaxChars(fld))>0) {
		if (max<tLen)
			tLen=max;
	} else
		max=tLen;

	mh=MemHandleNew(max+1);
	ErrFatalDisplayIf(mh==NULL, "(UIFieldSetText) Out of memory");

	tp=MemHandleLock(mh);
	if (tLen) 
		MemMove(tp, buffer, tLen);

	tp[tLen]='\x00';
	MemHandleUnlock(mh);

	oldH=FldGetTextHandle(fld);
	FldSetTextHandle(fld, mh);

	if (oldH)
		MemHandleFree(oldH);

	FldDrawField(fld);
}

/*
 * UIFieldScrollBarHandler
 *
 * Handler for scrollbar events.
 *
 *  -> ev		Event.
 *  -> fId		Field ID.
 *  -> sId		ScrollBar ID.
 *
 * Returns true if handled, false otherwise.
 */
Boolean
UIFieldScrollBarHandler(EventType *ev, UInt16 fId, UInt16 sId)
{
	if (ev->eType==fldChangedEvent) {
		if (ev->data.fldChanged.fieldID==fId) {
			UIFieldUpdateScrollBar(fId, sId);
			return true;
		}
	} else if (ev->eType==sclRepeatEvent) {
		if (ev->data.sclRepeat.scrollBarID==sId) {
			UIFieldScrollLines(fId, ev->data.sclRepeat.newValue-ev->data.sclRepeat.value);
			return true;
		}
	}

	return false;
}

/*
 * UIFieldScrollBarKeyHandler
 *
 * Handler for scrollbar key events.
 *
 *  -> ev		Event.
 *  -> fId		Field ID.
 *  -> sId		ScrollBar ID.
 *
 * Returns true if handled, false otherwise.
 */
Boolean
UIFieldScrollBarKeyHandler(EventType *ev, UInt16 fId, UInt16 sId)
{
	Int16 focusIndex;
	UInt16 focusId;

	if ((focusIndex=FrmGetFocus(currentForm))==noFocus)
		return false;

	if ((focusId=FrmGetObjectId(currentForm, focusIndex))==fId) {
		if (ev->data.keyDown.chr==pageUpChr) {
			UIFieldPageScroll(fId, sId, winUp);
			return true;
		} else if (ev->data.keyDown.chr==pageDownChr) {
			UIFieldPageScroll(fId, sId, winDown);
			return true;
		}
	}

	return false;
}

/*
 * UIFieldUpdateScrollBar
 *
 * Update scrollbar based on field attributes.
 *
 *  -> fId		Field ID.
 *  -> sId		ScrollBar ID.
 */
void
UIFieldUpdateScrollBar(UInt16 fId, UInt16 sId)
{
	FieldType *fld=UIObjectGet(fId);
	ScrollBarType *scr=UIObjectGet(sId);
	UInt16 mv=0, curPos, txtH, fldH;

	FldGetScrollValues(fld, &curPos, &txtH, &fldH);

	if (txtH>fldH)
		mv=txtH-fldH;
	else {
		if (curPos)
			mv=curPos;
	}

	SclSetScrollBar(scr, curPos, 0, mv, fldH-1);
}

/*
 * UIFieldScrollLines
 *
 * Scroll field number of lines.
 *
 *  -> fId		Field ID.
 *  -> num		Number of lines to scroll.
 */
void
UIFieldScrollLines(UInt16 fId, Int16 num)
{
	FieldType *fld=UIObjectGet(fId);

	if (num<0)
		FldScrollField(fld, -num, winUp);
	else
		FldScrollField(fld, num, winDown);
}

/*
 * UIFieldPageScroll
 *
 * Scroll field a page.
 *
 *  -> fId		Field ID.
 *  -> sId		ScrollBar ID.
 *  -> dir		Direction to scroll.
 */
void
UIFieldPageScroll(UInt16 fId, UInt16 sId, WinDirectionType dir)
{
	FieldType *fld=UIObjectGet(fId);

	if (FldScrollable(fld, dir)) {
		Int16 lts;

		lts=FldGetVisibleLines(fld)-1;

		if (dir==winUp)
			lts=-lts;

		UIFieldScrollLines(fId, lts);
		UIFieldUpdateScrollBar(fId, sId);
	}
}
