//---------------------------------------------------------------------------
/*
	TVP2 ( T Visual Presenter 2 )  A script authoring tool
	Copyright (C) 2000-2005  W.Dee <dee@kikyou.info>

	See details of license at "license.txt"
*/
//---------------------------------------------------------------------------
// Force Suicide User Confirmation Form
//---------------------------------------------------------------------------
#ifndef HaltWarnFormUnitH
#define HaltWarnFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TTVPHaltWarnForm : public TForm
{
__published:	// IDE �Ǘ��̃R���|�[�l���g
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TPaintBox *IconPaintBox;
	TButton *ExitButton;
	TButton *ContinueButton;
	void __fastcall IconPaintBoxPaint(TObject *Sender);
	void __fastcall ContinueButtonClick(TObject *Sender);
	void __fastcall ExitButtonClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// ���[�U�[�錾
public:		// ���[�U�[�錾
	__fastcall TTVPHaltWarnForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVPHaltWarnForm *TVPHaltWarnForm;
//---------------------------------------------------------------------------
#endif