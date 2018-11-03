#pragma once
#include "Layer4.h"
#include <array>
#define mult (0.05f)
class SelectBox : public BaseElement {
public:
	///MouseRegion regions[1];
	std::array<MouseRegion, 9> regionss;
	SelectBox (Vector2 pos, V2 size): BaseElement ("SelectBox", pos, size),
		regionss{ {
		//top
		MouseRegion (this,-size / 2, size / 20),
		MouseRegion (this,-size / 2 + size.GetXV()/2, size / 20),
		MouseRegion (this,-size / 2 + size.GetXV(), size / 20),	
		//middle
		MouseRegion (this, -size.GetXV()/2, size / 20),
		MouseRegion (this, 0, size/1.25),
		MouseRegion (this, +size.GetXV()/2, size / 20),
		//top
		MouseRegion (this,+size / 2, size / 20),
		MouseRegion (this,+size / 2 - size.GetXV()/2, size / 20),
		MouseRegion (this,+size / 2 - size.GetXV (), size / 20),
			} }
		
		//regionss { MouseRegion (this,-size / 2,0) }
	{
	}

	Vector2 GetStart() {
		Vector2 pos = property.GetAbs ();
		Vector2 size = property.GetSize ();
		Vector2 a = pos - size / 2;
		Vector2 b = pos + size / 2;
		return V2(min(a.x,b.x),min(a.y,b.y));
	}
	Vector2 GetSize() {
		return property.GetSize ();
	}
	Vector2 GetEnd() {
		Vector2 pos = property.GetAbs ();
		Vector2 size = property.GetSize ();
		Vector2 a = pos - size / 2;
		Vector2 b = pos + size / 2;
		return V2 (max (a.x, b.x), max (a.y, b.y));
	}

	void UpdateRegions () {
		Vector2 size = property.GetSize ();
		regionss[0].offset = -size / 2;
		regionss[1].offset = -size / 2 + size.GetXV () / 2;
		regionss[2].offset = -size / 2 + size.GetXV ();
		regionss[3].offset = -size.GetXV ()/2 ;
		regionss[4].offset = 0;
		regionss[5].offset = +size.GetXV () / 2;
		regionss[6].offset = +size / 2;
		regionss[7].offset = +size / 2 - size.GetXV ()/2;
		regionss[8].offset = +size / 2 - size.GetXV ();
		regionss[4].size = property.GetSize ().toAbs() / 1.25;
	}

	void Update () {
		MouseHelper* mhelper = BaseElement::io->mhelper;
		
		for (int i = 0; i < regionss.size (); i++) {
			auto one = regionss.at (i);
			one.Update ();
			Vector2 rev=0;


			if (one.isLockedOn ()) {
				if (i == 0) { rev = { -1 ,-1}; }
				if (i == 1) { rev = { 0 ,-1 }; }
				if (i == 2) { rev = { 1,-1 }; }
				if (i == 3) { rev = { -1,0 }; }
				if (i == 5) { rev = { 1,0 }; }
				if (i == 6) { rev = { 1,1 }; }
				if (i == 7) { rev = { 0,1 }; }
				if (i == 8) { rev = { -1,1 }; }

				V2 revdelta = mhelper->mouseDelta * rev*2;
				property.SetSize (property.GetSize() + revdelta);
		
			}
		

			if (i == 4) {
				if (one.isLockedOn ()) {
					property.SetRel (property.GetAbs () + BaseElement::io->mhelper->mouseDelta);
				}
			}
		}
		UpdateRegions ();
		
	}

	void Draw() {
		Vector2 size = property.GetSize ();
		if (size.x == 0 && size.y == 0) {
			return;
		}
		this->DrawBorder();
		this->DrawCorners();

		for (int i = 0; i < regionss.size (); i++) {
			auto one = regionss.at (i);
			one.Draw ();
		}
		
	
	}
};