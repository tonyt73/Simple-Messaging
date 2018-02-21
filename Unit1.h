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
//---------------------------------------------------------------------------
#include <vector>
#include <map>
#include <memory>
#include "..\Messaging\Messaging.h"
//---------------------------------------------------------------------------
//
class Event
{
private:
    String  m_Id;
public:
            __fastcall  Event(const String& id) : m_Id(id) {}

    __property  String  Id = { read = m_Id };
};
//---------------------------------------------------------------------------
class MessageInt : public Event
{
private:
    int m_Value;
public:
    __fastcall MessageInt(const String& id, int value)
    : Event(id)
    , m_Value(value)
    {
    }

    __property  int Value = { read = m_Value };
};
//---------------------------------------------------------------------------
class MessageString : public Event
{
private:
    String m_Value;
public:
    MessageString(const String& id, const String& value)
    : Event(id)
    , m_Value(value)
    {
    }

    __property  String Value = { read = m_Value };
};
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
    void __fastcall HandleEvent(const Event& message);
    void __fastcall HandleMessageInt1(const MessageInt& message);
    void __fastcall HandleMessageInt2(const MessageInt& message);
    void __fastcall HandleMessageString(const MessageString& message);

public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
