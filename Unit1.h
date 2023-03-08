//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Rest.Json.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Memo.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.Types.hpp>
#include <FMX.EditBox.hpp>
#include <FMX.NumberBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Memo.Types.hpp>
//---------------------------------------------------------------------------
#include <vector>
#include <map>
#include <memory>
#include "..\Messaging\Event.h"
#include "..\Messaging\Messaging.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TEdit *Edit1;
    TMemo *Memo1;
    TNumberBox *NumberBox1;
    TCheckBox *CheckBox1;
    TButton *Button1;
    TMemo *Memo2;
    void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar, TShiftState Shift);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall NumberBox1Change(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall CheckBox1Change(TObject *Sender);
private:	// User declarations
    ::Messaging::Registrar m_Registrar;

    void __fastcall OnEvent(const Event& message);
    void __fastcall OnChangeInt(const OnChange<int>& message);
    void __fastcall OnChangeString(const OnChange<String>& message);

public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
