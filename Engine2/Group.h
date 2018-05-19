#pragma once

#include "ItemManager.h"
class GroupBox: public ItemManager, public Element {

public:
	Vector2 size;
	Color bkclr = Colors::TKEY;

	void SelfDraw() {
		if (bkclr == Colors::TKEY) {
			int depth = GetDepth();
			Color colors[] = { Colors::White, Colors::GrayLightLight, Colors::GrayLight, Colors::Gray };
			depth %= sizeof(colors) / sizeof(colors[0]);
			io->out->paint->rectangle(GetPos().x, GetPos().y, size.x, size.y, colors[depth]);
		}
		else {
			io->out->paint->rectangle(GetPos().x, GetPos().y, size.x, size.y, bkclr);
		}
		io->out->paint->rectangleBorder(GetPos().x, GetPos().y, size.x, size.y, Colors::Black, 2);
		
	}

	void Draw() {
		SelfDraw();
		for (Element* Item : Items) {
			Item->Draw();
		}
	}

	void Update() override {
		for (Element* Item : Items) {
			Item->Update();
		}
	}



	void Add(Element* item) {
		if (item->ID == this->ID) return;
		ItemManager::Add(item);
		item->parent = this;
	}

	GroupBox(Vector2 pos, Vector2 size): Element(pos),size(size) {
	}

	GroupBox(Vector2 pos, Vector2 size, Color bkclr) : Element(pos), size(size), bkclr(bkclr) {
	}

};
