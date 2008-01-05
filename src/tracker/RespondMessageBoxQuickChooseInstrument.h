/*
 *  RespondMessageBoxQuickChooseInstrument.h
 *  MilkyTracker
 *
 *  Created by Peter Barth on 25.10.05.
 *  Copyright (c) 2005 milkytracker.net, All rights reserved.
 *
 */

#ifndef RESPONDMESSAGEBOXQUICKCHOOSEINSTRUMENT__H
#define RESPONDMESSAGEBOXQUICKCHOOSEINSTRUMENT__H

#include "RespondMessageBox.h"

class RespondMessageBoxQuickChooseInstrument : public RespondMessageBox
{
private:
	pp_int32 value;
	pp_int32 valueRangeStart, valueRangeEnd, valueIncreaseStep;
	
public:
	RespondMessageBoxQuickChooseInstrument(PPScreen* screen, 
										   RespondListenerInterface* responder,
										   pp_int32 id,
										   const PPString& caption);

	pp_int32 getValue() { return value; }
	
	void setValue(pp_int32 val) { if (val < valueRangeStart) val = valueRangeStart; if (val > valueRangeEnd) val = valueRangeEnd; value = val; updateListBoxes(); }

	void setValueCaption(const PPString& caption);

	virtual void show();

	virtual pp_int32 handleEvent(PPObject* sender, PPEvent* event);	

	static pp_uint16 numPadKeyToValue(pp_uint16 keyCode);

private:
	void fitListBoxes();
	
	void fitListBox(pp_int32 id, pp_int32 valueRangeStart, pp_int32 valueRangeEnd);

	void updateListBoxes();
	
	void updateListBox(pp_int32 id, pp_int32 val);
	
	void listBoxEnterEditState(pp_int32 id);
	
	void commitChanges();
};

#endif

