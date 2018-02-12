#pragma once
#include "ItemManager.h"
class GuiElementManager : public ItemManager {
protected:
	virtual void SelfUpdate() = 0;
	virtual void SelfDraw() = 0;
	virtual void Build() = 0;
public:
	IOgroup * io = nullptr;
	GuiElementManager(IOgroup* io) : io(io) {}

	void Update() {
		UpdateItems();
		SelfUpdate();
	}

	void Draw() {
		SelfDraw();
		DrawItems();
	}

	void UpdateItems() {
		for (int i = 0; io != nullptr && i < Items.size(); i++) {
			this->UpdateOne(Items[i]);
		}
	}

	void DrawItems() {
		for (int i = 0; io != nullptr && i < Items.size(); i++) {
			this->DrawOne(Items[i]);
		}
	}

	void UpdateOne(ManageableElement* e) {
		e->Update(io);
	}
	void DrawOne(ManageableElement* e) {
		e->Draw(io);
	}

};

