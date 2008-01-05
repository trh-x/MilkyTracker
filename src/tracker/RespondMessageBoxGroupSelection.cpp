/*
 *  RespondMessageBoxGroupSelection.cpp
 *  MilkyTracker
 *
 *  Created by Peter Barth on 23.06.06.
 *  Copyright (c) 2006 milkytracker.net, All rights reserved.
 *
 */

#include "RespondMessageBoxGroupSelection.h"
#include "SimpleVector.h"
#include "Screen.h"
#include "StaticText.h"
#include "MessageBoxContainer.h"
#include "Font.h"
#include "ListBox.h"
#include "RadioGroup.h"
#include "Seperator.h"
#include "ControlIDs.h"

RespondMessageBoxGroupSelection::RespondMessageBoxGroupSelection(PPScreen* screen, 
					  RespondListenerInterface* responder,
					  pp_int32 id,
					  const PPString& caption,
					  const PPSimpleVector<PPString>& choices) :
	RespondMessageBox()
{
	PPFont* font = PPFont::getFont(PPFont::FONT_SYSTEM);

	initRespondMessageBox(screen, responder, id, caption, 290, 74 + choices.size()*(font->getCharHeight() + PPRadioGroup::eDefaultSpacerHeight + 1), 26, "Ok", "Cancel");

	pp_int32 i, j = 0;
	
	j = 0;
	for (i = 0; i < choices.size(); i++)
	{
		pp_int32 size = choices.get(i)->length()*font->getCharWidth() + PPRadioGroup::eDefaultRadioWidth;
		if (size > j) j = size;
	}

	pp_int32 x = getMessageBoxContainer()->getLocation().x;
	pp_int32 y = getMessageBoxContainer()->getLocation().y;
	
	pp_int32 width = getMessageBoxContainer()->getSize().width;
	pp_int32 height = getMessageBoxContainer()->getSize().height;
	
	pp_int32 x2 = x + (width / 2) - (j / 2);
	pp_int32 y2 = getMessageBoxContainer()->getControlByID(MESSAGEBOX_STATICTEXT_MAIN_CAPTION)->getLocation().y;
	y2+=12;

	PPRadioGroup* radioGroup = new PPRadioGroup(MESSAGEBOX_CONTROL_USER1, screen, this, PPPoint(x2, y2), PPSize(0,0)); 
	radioGroup->setFont(font);
	for (i = 0; i < choices.size(); i++)
		radioGroup->addItem(*choices.get(i));
	radioGroup->fitSize();
	radioGroup->setColor(getMessageBoxContainer()->getColor());

	getMessageBoxContainer()->addControl(radioGroup);

	selection = 0;
}

pp_int32 RespondMessageBoxGroupSelection::handleEvent(PPObject* sender, PPEvent* event)
{
	if (event->getID() == eSelection)
	{
		switch (reinterpret_cast<PPControl*>(sender)->getID())
		{
			case MESSAGEBOX_CONTROL_USER1:
				this->selection = reinterpret_cast<PPRadioGroup*>(sender)->getChoice();
				break;
		}
	}
	
	return RespondMessageBox::handleEvent(sender, event);
}

