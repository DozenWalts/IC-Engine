#ifndef __CHAT_H__
#define __CHAT_H__
//=============================================================================
#include "UI_Panel.h"
#include "Core.h"
#include "Sys/Input.h"
#include "Render/Render.h"
#include "Sys/Socket.h"
//=============================================================================
struct Chat /*: UI_Panel*/ {
	UI_Panel *ChatPanel;
	UI_Panel *TextPanel;
	UI_Panel *InputPanel;
	Chat() {}
	void add_chat_ui() {
		GUI &UI = *_Gui;
		UI_Panel *Main = UI.find("Main");
		ChatPanel = UI.ADD(GUI::PANEL, "Chat", Main)->windowLH(Main, 0.03f, 0.05f, 0.3f, 0.5f);

		// dest ip
		UI_Panel *Dest_ip = UI.ADD(GUI::EDIT_T, "Dest_ip", ChatPanel)->windowLH(ChatPanel, 5, 5, 50 * _Render->Font.m_width, _Render->Font.m_height);
		Dest_ip->void_lambda = [](UI_Panel *p) {
			if (_Input->lmouse[0]) {
				LOG::msg("read ip [%s]", _Net->dst.print());
				p->caption.print("%s", _Net->dst.print());
			}
			if (p->caption.size > 8 && !_Input->key[K_SPACE]) {
				//CON.write(0,"set [%s]",p->caption.text);
				_Net->dst.set(p->caption.text);
				_Net->out.to.set(p->caption.text);
				LOG::msg("set ip [%s]->[%s]", p->caption.text, _Net->dst.print());
			}
			if (_Input->keyp(K_ENTER)) {
				_Net->try_connect();
			}
			p->caption.print("%s", _Net->dst.print());
		};
		Dest_ip->OnClick();
		//Dest_ip->caption.print("%s",_Net->dst.print());
		Dest_ip->style = 1;//text left allign

		// current message input
		InputPanel = UI.ADD(GUI::EDIT_T, "Chat_input", ChatPanel)->AFTER(Dest_ip, 5)->w_to_w(ChatPanel, -5);
		InputPanel->style = 1;//text left allign
		InputPanel->void_lambda = [](UI_Panel *p) {   //on enter add text to chat_text
			if (_Input->key[K_INS]) {
				u32_t wcmd = ('w') | ('c' << 8) | ('m' << 16) | ('R' << 24);
				_Net->Sbuf.write(&wcmd, 4);
				u8_t cmd = 1;
				_Net->Sbuf.write(&cmd, 1);
				//_Net->Sbuf.write("test_cmd", 8);

				p->param->caption += "wcmd";

				p->caption.size = p->t_cur_pos = 0;
				p->param->set_scroll_lim();
				p->param->ScrollSet(p->param->sx, -p->param->t_max.y);//R.scrollx

			}
			if (_Input->key[K_ENTER] && p->caption.size > 0) {
				_Net->Sbuf.write(p->caption.text, p->caption.size);         //NET SEND
				if (_Net->Sbuf.buf[_Net->Sbuf.size - 1] == '\n')_Net->Sbuf.size--;
				//_Net->Sbuf.ready = 1;
				//p->param= are set below since there lambda     
				p->param->caption += p->caption;//add line
				p->caption.size = p->t_cur_pos = 0;// caption.pos = 0;//clear input text  p->caption.ss??
				//p->param->update_text_lines();
				p->param->set_scroll_lim();
				p->param->ScrollSet(p->param->sx, -p->param->t_max.y);//R.scrollx
				//p->param->R.scrolly=-p->param->R.scrolllimy;
			}
		};//end lambda

		// chat log   UI_EDIT/UI_PANEL
		TextPanel = UI.ADD(GUI::EDIT_T, "Chat_text", ChatPanel)->xy_to_xy(ChatPanel, 5, 5)->wh_to_wy(InputPanel, 0, -5);
		TextPanel->filled = true;
		TextPanel->style = 1;//text left allign

		InputPanel->param = TextPanel;//!!!! for lambda

		//float tval = 0.0f;
		//float temp = tval / Chat_text->x / tval;
		//LOG::msg("val = %f", temp);

		ChatPanel->vis = false;
	}
	void update() {
		if (_Input->keyp(K_F2)) {
			//UI_Panel *ChatPanel = _Gui->find("Chat", _Gui->find("Main"));
			if (ChatPanel) {
				ChatPanel->vis = !ChatPanel->vis;
			}
		}
		if (_Net->Rbuf.size) {//_Net->Rbuf.ready && 
			//UI_Panel *MainChatText = _Gui->find("Chat_text", _Gui->find("Chat", _Gui->find("Main")));
			str tstr(0, "%s", (char*)_Net->Rbuf.buf);//tstr.size--;
			TextPanel->caption += tstr;
			TextPanel->set_scroll_lim();
			TextPanel->ScrollSet(TextPanel->sx, -TextPanel->t_max.y);//scroll down
			_Net->Rbuf.reset();
			//_Net->Rbuf.ready = 0;
		}
	}

};
//=============================================================================
#endif
