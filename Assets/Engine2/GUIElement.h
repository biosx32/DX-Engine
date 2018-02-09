#pragma once

class ElementController {
	int selectedID; //is modified if control has select event
};

template <class T>
class Element {
	int x, y;
	bool visible;
	int ID;
	int group; //podla group offsetni suradnice pri kresleni gui
};

class GroupBox {

};

class Button {

};

