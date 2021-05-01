#ifndef __UI_ICON__
#define __UI_ICON__

#include "UI_Panel.h"
#include "Render/Render.h"
#include "Sys/GlyphMap.h"

struct Icon final: UI_Widget {// panel->mul holds icon texture id
	virtual void Draw_UI()override{
		if(!panel->Expanded)return;
		float b = _Render->Font.m_height;//border
		//panel->pyh=false;
		panel->yh = (panel->width() + b);//panel->to_loc_yh(panel->gy+panel->width() + b);
		panel->gyh = panel->gy + panel->width() + b;//panel->to_screen_yh(panel->yh);
		//panel->yh = panel->to_loc_yh(panel->gyh);
		//panel->update_position();
		//panel->update_VP(GUI.VP);
		u32_t id = panel->mul;
		//const u32_t uc = utf32("Y");
		//GlyphMap::GlyphHash::Element *rez = _Render->Font._glyphs.get(&uc, (const char*)&uc, sizeof(u32_t));
		//_Render->DrawText2D();?
		_Render->TextQuad2D(
			vec2(panel->gx, panel->gy+b), vec2(panel->gx, panel->gyh), 
			vec2(panel->gxw, panel->gyh), vec2(panel->gxw, panel->gy+b), 
			vec4(1,1,1,1), vec4(0, 1, 1, 0), id);//	rez->second->uv
	}
	//void Update_GUI(const float &dt){};
	//virtual void Input_UI() {
	//	if (panel && panel->inm && _Input->mouse_end_click(0)) 
	//	{
	//		
	//	}
	//}
};

#endif
