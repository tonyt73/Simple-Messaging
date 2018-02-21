//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop
#include <System.TypInfo.hpp>
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    // map subscriptions to handlers
    ::Messaging::Bus::Subscribe<Event>(HandleEvent);
    ::Messaging::Bus::Subscribe<MessageInt>(HandleMessageInt1); // first subscription for MessageInt
    ::Messaging::Bus::Subscribe<MessageInt>(HandleMessageInt2); // second subscription for MessageInt i.e. multiple destinations for same data/event
    ::Messaging::Bus::Subscribe<MessageString>(HandleMessageString);
}
//---------------------------------------------------------------------------
// send messages/events
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit1KeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar, TShiftState Shift)
{
    ::Messaging::Bus::Publish(MessageString("Edit1.Text.Changed",Edit1->Text));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::NumberBox1Change(TObject *Sender)
{
    ::Messaging::Bus::Publish(MessageInt("NumberBox1.Value.Changed", NumberBox1->Value));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    ::Messaging::Bus::Publish(Event("LoadData"));
    ::Messaging::Bus::Publish(MessageInt("Button1.Click",73));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox1Change(TObject *Sender)
{
    ::Messaging::Bus::Publish(Event("RefreshList"));
    ::Messaging::Bus::Publish(MessageInt("CheckBox1.IsChecked.Changed", CheckBox1->IsChecked ? 1 : 0));
}
//---------------------------------------------------------------------------
// Handlers
//---------------------------------------------------------------------------
void __fastcall TForm1::HandleEvent(const Event& message)
{
    Form1->Memo1->Lines->Add("Event: " + message.Id);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::HandleMessageInt1(const MessageInt& message)
{
    Form1->Memo1->Lines->Add(message.Id + "=" + IntToStr(message.Value));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::HandleMessageInt2(const MessageInt& message)
{
    Form1->Memo2->Lines->Add(message.Id + "=" + IntToStr(message.Value));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::HandleMessageString(const MessageString& message)
{
    auto msg = message;
    Form1->Memo1->Lines->Add(msg.Id + "=" + msg.Value);
}
//---------------------------------------------------------------------------

