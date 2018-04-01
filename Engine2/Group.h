#pragma once


#include "ManageableElement.h"
#include "ItemManager.h"
class GroupBox: public ItemManager, public ManageableElement {

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

	void Draw() override {
		SelfDraw();
		for (ManageableElement* Item : Items) {
			Item->Draw(io);
		}
	}

	void Update() override {
		for (ManageableElement* Item : Items) {
			Item->Update(io);
		}
	}



	void Add(ManageableElement* item) {
		if (item->ID == this->ID) return;
		ItemManager::Add(item);
		item->parent = this;
		item->pDepth = this->pDepth + 1;
	}

	GroupBox(Vector2 pos, Vector2 size): ManageableElement(pos),size(size) {
	}

	GroupBox(Vector2 pos, Vector2 size, Color bkclr) : ManageableElement(pos), size(size), bkclr(bkclr) {
	}

};
