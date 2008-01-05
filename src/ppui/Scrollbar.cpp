#include "ScrollBar.h"
#include "GraphicsAbstract.h"
#include "Button.h"
#include "Event.h"
#include "Screen.h"
#include "Seperator.h"

class SliderButton : public PPButton
{
private:
	PPSeperator* seperators[3];
	bool horizontal;

public:
	SliderButton(pp_int32 id, PPScreen* parentScreen, EventListenerInterface* eventListener, 
				 PPPoint location, PPSize size, bool border = true, bool clickable = true, bool update = true, bool horiz = true) :
		PPButton(id, parentScreen, eventListener, location, size, border, clickable, update),
		horizontal(horiz)
	{
		seperators[0] = new PPSeperator(0, parentScreen, PPPoint(0, 0), SCROLLBUTTONSIZE - 6, *getColor(), !horizontal);
		seperators[1] = new PPSeperator(0, parentScreen, PPPoint(0, 0), SCROLLBUTTONSIZE - 6, *getColor(), !horizontal);
		seperators[2] = new PPSeperator(0, parentScreen, PPPoint(0, 0), SCROLLBUTTONSIZE - 6, *getColor(), !horizontal);
	}
	
	virtual ~SliderButton()
	{
		delete seperators[0];
		delete seperators[1];
		delete seperators[2];
	}
	
	virtual void paint(PPGraphicsAbstract* g)
	{
		if (!isVisible())
			return;

		PPButton::paint(g);
		
		if ((horizontal && getSize().width < 20) ||
			(!horizontal && getSize().height < 20)) 
			return;
		
		PPPoint p(horizontal ? getLocation().x + getSize().width / 2 - 4 : getLocation().x + 2, 
				  horizontal ? getLocation().y + 2 : getLocation().y + getSize().height / 2 - 3);

		if (isPressed())
		{
			p.x++;
			p.y++;
		}
		
		for (pp_int32 i = 0; i < 3; i++)
		{
			seperators[0]->setLocation(p);
			seperators[0]->paint(g);
			if (horizontal)
				p.x+=3;
			else
				p.y+=2;
		}		
	}
};

void PPScrollbar::initButtons()
{
	PPPoint buttonDownPos, buttonBarPos;
	PPSize buttonBarSize;

	if (horizontal)
	{
		this->size.height = SCROLLBUTTONSIZE;
		this->size.width = oneDimSize;
	
		buttonDownPos = PPPoint(location.x + oneDimSize - SCROLLBUTTONSIZE, location.y);
	
		buttonBarPos = PPPoint(location.x + SCROLLBUTTONSIZE, location.y);
	
		buttonBarSize = PPSize((oneDimSize - SCROLLBUTTONSIZE*2), SCROLLBUTTONSIZE);  
	}
	else
	{
		this->size.width = SCROLLBUTTONSIZE;
		this->size.height = oneDimSize;
		
		buttonDownPos = PPPoint(location.x, location.y + oneDimSize - SCROLLBUTTONSIZE);
		
		buttonBarPos = PPPoint(location.x, location.y + SCROLLBUTTONSIZE);
		
		buttonBarSize = PPSize(SCROLLBUTTONSIZE, (oneDimSize - SCROLLBUTTONSIZE*2));  
	}

	backgroundButton = new PPButton(0, parentScreen, NULL, /*_Point(location.x + (horizontal?0:1), location.y + (horizontal?1:0))*/location, this->size, false);
	backgroundButton->setColor(backgroundColor);
	backgroundButton->setInvertShading(true);

	buttonUp = new PPButton(0, parentScreen, this, location, PPSize(SCROLLBUTTONSIZE,SCROLLBUTTONSIZE), false);

	SimpleBitmap b = buttonUp->getBitmap();

	{
		const pp_int32 size = (b.width>>1)-2;

		const pp_int32 xo = ((b.width >> 1) - size)-1;
		const pp_int32 yo = ((b.width >> 1) - (size>>1))-1;

		for (pp_int32 j = 0; j <= size; j++)
			for (pp_int32 i = 0; i < (size*2+1)-j*2; i++)
			{
				pp_uint8* buf;

				pp_int32 x = i+j, y = j;
				
				if (horizontal)
					buf = (pp_uint8*)b.buffer+((x+xo)*b.width+((size-y)+yo))*3;
				else
					buf = (pp_uint8*)b.buffer+(((size-y)+yo)*b.width+(x+xo))*3;
				
				buf[0] = 1;
				buf[1] = 1;
				buf[2] = 1;
				//g->setPixel(x+i+j,y+j);
			}
	}

	/*for (x = 1; x < b.width-4; x++)
	{
		pp_int32 y2 = (x>>1)+(b.height>>1);
		pp_int32 y1 = (b.height-1)-((x>>1)+(b.height>>1));
		
		for (y = y1; y < y2; y++)
		{
			
			pp_uint8* buf;

			if (horizontal)
				buf = (pp_uint8*)b.buffer+(y*b.width+x+1)*3;
			else
				buf = (pp_uint8*)b.buffer+((x+1)*b.width+y)*3;

			buf[0] = 1;
			buf[1] = 1;
			buf[2] = 1;
		}
	}*/

	buttonDown = new PPButton(0, parentScreen, this, buttonDownPos , PPSize(SCROLLBUTTONSIZE,SCROLLBUTTONSIZE), false);

	b = buttonDown->getBitmap();
	/*for (x = 1; x < b.width-4; x++)
	{
		pp_int32 y2 = (x>>1)+(b.height>>1);
		pp_int32 y1 = (b.height-1)-((x>>1)+(b.height>>1));
		
		for (y = y1; y < y2; y++)
		{
			
			pp_uint8* buf;

			if (horizontal)
				buf = (pp_uint8*)b.buffer+(y*b.width+(b.width-1-(x+1)))*3;
			else
				buf = (pp_uint8*)b.buffer+((b.height-1-(x+1))*b.width+y)*3;

			buf[0] = 1;
			buf[1] = 1;
			buf[2] = 1;
		}
	}*/
	{
		const pp_int32 size = (b.width>>1)-2;

		const pp_int32 xo = ((b.width >> 1) - size)-1;
		const pp_int32 yo = ((b.width >> 1) - (size>>1))-1;

		for (pp_int32 j = 0; j <= size; j++)
			for (pp_int32 i = 0; i < (size*2+1)-j*2; i++)
			{
				pp_uint8* buf;

				pp_int32 x = i+j, y = j;
				
				if (horizontal)
					buf = (pp_uint8*)b.buffer+((x+xo)*b.width+(y+yo))*3;
				else
					buf = (pp_uint8*)b.buffer+((y+yo)*b.width+(x+xo))*3;
				
				buf[0] = 1;
				buf[1] = 1;
				buf[2] = 1;
				//g->setPixel(x+i+j,y+j);
			}
	}
	
	buttonBar = new SliderButton(0, parentScreen, this, buttonBarPos, buttonBarSize, false, false, true, horizontal);
	/*if (!horizontal)
	{
		buttonBar->setVerticalShading(false);
		backgroundButton->setVerticalShading(false);
	}*/

	setBarSize(currentBarSize);
	setBarPosition(currentBarPosition);
}

PPScrollbar::PPScrollbar(pp_int32 id, PPScreen* parentScreen, EventListenerInterface* eventListener, PPPoint location, pp_int32 size, bool horizontal) :
	PPControl(id, parentScreen, eventListener, location, PPSize(0,0)),
	oneDimSize(size),
	horizontal(horizontal),
	controlCaughtByLMouseButton(false), controlCaughtByRMouseButton(false),
	currentBarSize(65536), currentBarPosition(0)
{
	// default color
	backgroundColor.r = 32;
	backgroundColor.g = 48;
	backgroundColor.b = 64;

	initButtons();

	caughtControl = NULL;

}

PPScrollbar::~PPScrollbar()
{
	delete backgroundButton;
	
	delete buttonUp;

	delete buttonDown;

	delete buttonBar;
}

void PPScrollbar::paint(PPGraphicsAbstract* g)
{
	if (!isVisible())
		return;

	backgroundButton->paint(g);

	buttonDown->paint(g);

	buttonUp->paint(g);

	buttonBar->paint(g);
}

void PPScrollbar::setBarSize(pp_int32 size, bool repaint /* = true */)
{
	if (size < 0) size = 0;
	if (size > 65536) size = 65536;

	currentBarSize = size;
	
	pp_int32 newSize = (((horizontal?this->size.width:this->size.height) - SCROLLBUTTONSIZE*2) * size)>>16;

	if (horizontal)
	{
		buttonBar->setSize(PPSize(newSize, this->size.height));		
	}
	else
	{
		buttonBar->setSize(PPSize(this->size.width, newSize));
	}

	if (repaint)
		parentScreen->paintControl(this);

}

void PPScrollbar::setBarPosition(pp_int32 pos, bool repaint /* = true */)
{
	if (pos < 0) pos = 0;
	if (pos > 65536) pos = 65536;

	currentBarPosition = pos;

	pp_int32 size = (horizontal?buttonBar->getSize().width:buttonBar->getSize().height);

	pp_int32 entireSize = (horizontal?this->size.width:this->size.height) - SCROLLBUTTONSIZE*2;

	pp_int32 maxPos = entireSize-size;

	pp_int32 newPos = (maxPos*pos)>>16;	

	PPPoint p = location;

	if (horizontal)
		p.x+=newPos + SCROLLBUTTONSIZE;
	else
		p.y+=newPos + SCROLLBUTTONSIZE;

	buttonBar->setLocation(p);

	if (repaint)
		parentScreen->paintControl(this);
}

pp_int32 PPScrollbar::callEventListener(PPEvent* event)
{
	//if (!visible)
	//	return 0;

	switch (event->getID())
	{
		case eLMouseDown:
		{
			PPPoint* p = (PPPoint*)event->getDataPtr();

			if (buttonUp->hit(*p))
			{
				caughtControl = buttonUp;
				caughtControl->callEventListener(event);
				controlCaughtByLMouseButton = true;
			}
			else if (buttonDown->hit(*p))
			{
				caughtControl = buttonDown;
				caughtControl->callEventListener(event);				
				controlCaughtByLMouseButton = true;
			}
			else if (buttonBar->hit(*p))
			{
				caughtControl = buttonBar;
				// -------------------------
				buttonBar->setPressed(true);
				parentScreen->paintControl(buttonBar);
				// -------------------------
				caughtMouseLocation = *p;
				caughtControlLocation = buttonBar->getLocation();
				caughtControl->callEventListener(event);				
				controlCaughtByLMouseButton = true;
			}
			else if (backgroundButton->hit(*p))
			{
				handleEvent(reinterpret_cast<PPObject*>(backgroundButton), event);				
			}

			break;
		}

		case eLMouseUp:
			controlCaughtByLMouseButton = false;

			if (caughtControl == NULL)
				break;

			if (controlCaughtByRMouseButton)
			{
				caughtControl->callEventListener(event);
				break;
			}

			// -------------------------
			if (reinterpret_cast<PPButton*>(caughtControl) == buttonBar)
			{
				buttonBar->setPressed(false);
				parentScreen->paintControl(buttonBar);
			}
			// -------------------------

			caughtControl->callEventListener(event);
			caughtControl = NULL;
			break;

		case eLMouseRepeat:
		{
			if (caughtControl)
			{
				caughtControl->callEventListener(event);
				break;
			}
			else
			{
				PPPoint* p = (PPPoint*)event->getDataPtr();
				/*if (backgroundButton->hit(*p))
				{
					handleEvent(reinterpret_cast<PPObject*>(backgroundButton), event);				
				}
				PPPoint* p = (PPPoint*)event->getDataPtr();*/
				if (backgroundButton->hit(*p) && !buttonBar->hit(*p))
				{
					handleEvent(reinterpret_cast<PPObject*>(backgroundButton), event);				
				}
				else if (buttonBar->hit(*p))
				{
					// -------------------------
					buttonBar->setPressed(true);
					parentScreen->paintControl(buttonBar);
					// -------------------------

					caughtControl = buttonBar;
					caughtMouseLocation = *p;
					caughtControlLocation = buttonBar->getLocation();
					caughtControl->callEventListener(event);				
				}

			}
			break;
		}

		case eRMouseDown:
		{
			PPPoint* p = (PPPoint*)event->getDataPtr();

			if (buttonUp->hit(*p))
			{
				caughtControl = buttonUp;
				caughtControl->callEventListener(event);
				controlCaughtByRMouseButton = true;
			}
			else if (buttonDown->hit(*p))
			{
				caughtControl = buttonDown;
				caughtControl->callEventListener(event);				
				controlCaughtByRMouseButton = true;
			}
			else if (buttonBar->hit(*p))
			{
				caughtControl = buttonBar;
				// -------------------------
				buttonBar->setPressed(true);
				parentScreen->paintControl(buttonBar);
				// -------------------------
				caughtMouseLocation = *p;
				caughtControlLocation = buttonBar->getLocation();
				caughtControl->callEventListener(event);				
				controlCaughtByRMouseButton = true;
			}
			else if (backgroundButton->hit(*p))
			{
				handleEvent(reinterpret_cast<PPObject*>(backgroundButton), event);				
			}

			break;
		}

		case eRMouseUp:
			controlCaughtByRMouseButton = false;

			if (caughtControl == NULL)
				break;

			if (controlCaughtByLMouseButton)
			{
				caughtControl->callEventListener(event);
				break;
			}

			// -------------------------
			if (reinterpret_cast<PPButton*>(caughtControl) == buttonBar)
			{
				buttonBar->setPressed(false);
				parentScreen->paintControl(buttonBar);
			}
			// -------------------------

			caughtControl->callEventListener(event);
			caughtControl = NULL;
			break;

		case eRMouseRepeat:
		{
			if (caughtControl)
			{
				caughtControl->callEventListener(event);
				break;
			}
			else
			{
				/*PPPoint* p = (PPPoint*)event->getDataPtr();
				if (backgroundButton->hit(*p))
				{
					handleEvent(reinterpret_cast<PPObject*>(backgroundButton), event);				
				}*/
				PPPoint* p = (PPPoint*)event->getDataPtr();
				if (backgroundButton->hit(*p) && !buttonBar->hit(*p))
				{
					handleEvent(reinterpret_cast<PPObject*>(backgroundButton), event);				
				}
				else if (buttonBar->hit(*p))
				{
					// -------------------------
					buttonBar->setPressed(true);
					parentScreen->paintControl(buttonBar);
					// -------------------------

					caughtControl = buttonBar;
					caughtMouseLocation = *p;
					caughtControlLocation = buttonBar->getLocation();
					caughtControl->callEventListener(event);				
				}

			}
			break;
		}

		//case eLMouseDrag:
		default:
			if (caughtControl == NULL)
				break;

			caughtControl->callEventListener(event);
			break;

	}
	
	return 0;
}

pp_int32 PPScrollbar::handleEvent(PPObject* sender, PPEvent* event)
{

	if (
		(event->getID() == eLMouseUp &&
		sender == reinterpret_cast<PPObject*>(buttonUp)) ||
		(event->getID() == eLMouseRepeat &&
		sender == reinterpret_cast<PPObject*>(buttonUp)) ||
		(event->getID() == eRMouseUp &&
		sender == reinterpret_cast<PPObject*>(buttonUp)) ||
		(event->getID() == eRMouseRepeat &&
		sender == reinterpret_cast<PPObject*>(buttonUp))
		)
	{
		// Call parent event listener
		PPEvent e(eBarScrollUp);
		return eventListener->handleEvent(reinterpret_cast<PPObject*>(this), &e);
	}
	if (
		(event->getID() == eLMouseUp &&
		sender == reinterpret_cast<PPObject*>(buttonDown)) ||
		(event->getID() == eLMouseRepeat &&
		sender == reinterpret_cast<PPObject*>(buttonDown)) ||
		(event->getID() == eRMouseUp &&
		sender == reinterpret_cast<PPObject*>(buttonDown)) ||
		(event->getID() == eRMouseRepeat &&
		sender == reinterpret_cast<PPObject*>(buttonDown))
		)
	{
		// Call parent event listener
		PPEvent e(eBarScrollDown);
		return eventListener->handleEvent(reinterpret_cast<PPObject*>(this), &e);
	}
	else if (/*event->getID() == eLMouseDown &&*/
			 sender == reinterpret_cast<PPObject*>(backgroundButton))
	{
		
		if (horizontal)
		{
			PPPoint* p = (PPPoint*)event->getDataPtr();
			
			if (p->x < buttonBar->getLocation().x)
			{
				pp_int32 bsize = buttonBar->getSize().width;
				pp_int32 entireSize = size.width - SCROLLBUTTONSIZE*2;

				float f = (float)entireSize/(float)(entireSize - bsize);

				currentBarPosition-=(pp_int32)(currentBarSize*f);
				if (currentBarPosition < 0) currentBarPosition = 0;
				setBarPosition(currentBarPosition);
				
				// Call parent event listener
				PPEvent e(eBarPosChanged);
				return eventListener->handleEvent(reinterpret_cast<PPObject*>(this), &e);
			}
			else if (p->x > buttonBar->getLocation().x + buttonBar->getSize().width)
			{
				pp_int32 bsize = buttonBar->getSize().width;
				pp_int32 entireSize = size.width - SCROLLBUTTONSIZE*2;

				float f = (float)entireSize/(float)(entireSize - bsize);

				currentBarPosition+=(pp_int32)(currentBarSize*f);
				if (currentBarPosition > 65536) currentBarPosition = 65536;
				setBarPosition(currentBarPosition);
				
				// Call parent event listener
				PPEvent e(eBarPosChanged);
				return eventListener->handleEvent(reinterpret_cast<PPObject*>(this), &e);
			}
		}
		else 
		{
			PPPoint* p = (PPPoint*)event->getDataPtr();
			
			if (p->y < buttonBar->getLocation().y)
			{
				pp_int32 bsize = buttonBar->getSize().height;
				pp_int32 entireSize = size.height - SCROLLBUTTONSIZE*2;

				float f = (float)entireSize/(float)(entireSize - bsize);

				currentBarPosition-=(pp_int32)(currentBarSize*f);
				if (currentBarPosition < 0) currentBarPosition = 0;
				setBarPosition(currentBarPosition);
				
				// Call parent event listener
				PPEvent e(eBarPosChanged);
				return eventListener->handleEvent(reinterpret_cast<PPObject*>(this), &e);
			}
			else if (p->y > buttonBar->getLocation().y + buttonBar->getSize().height)
			{
				pp_int32 bsize = buttonBar->getSize().height;
				pp_int32 entireSize = size.height - SCROLLBUTTONSIZE*2;

				float f = (float)entireSize/(float)(entireSize - bsize);

				currentBarPosition+=(pp_int32)(currentBarSize*f);
				if (currentBarPosition > 65536) currentBarPosition = 65536;
				setBarPosition(currentBarPosition);
				
				// Call parent event listener
				PPEvent e(eBarPosChanged);
				return eventListener->handleEvent(reinterpret_cast<PPObject*>(this), &e);
			}
		}
				

	}
	else if ((event->getID() == eLMouseDrag && 
			 sender == reinterpret_cast<PPObject*>(buttonBar)) ||
			 (event->getID() == eRMouseDrag && 
			 sender == reinterpret_cast<PPObject*>(buttonBar)))
	{
		PPPoint* p = (PPPoint*)event->getDataPtr();
	
		pp_int32 pos = 0,dx,nx;

		if (horizontal)
		{

			dx = (p->x - caughtMouseLocation.x);
			
			/*if (dx < 0)
			{
				__asm
				{
					int 3
				}
			}*/
			
			nx = caughtControlLocation.x + dx;
			//if (nx < location.x + SCROLLBUTTONSIZE)
			//	nx = location.x + SCROLLBUTTONSIZE;
			//if (nx > location.x + size.width - SCROLLBUTTONSIZE*2 - buttonBar->getSize().width)
			//	nx = location.x + size.width - SCROLLBUTTONSIZE*2 - buttonBar->getSize().width;
			
			nx-=(location.x + SCROLLBUTTONSIZE);
			
			pp_int32 d = (size.width - buttonBar->getSize().width - SCROLLBUTTONSIZE*2);
			
			if (d != 0)
				pos = nx*65536 / d;			
		}
		else
		{
			dx = (p->y - caughtMouseLocation.y);
			
			/*if (dx < 0)
			{
				__asm
				{
					int 3
				}
			}*/
			
			nx = caughtControlLocation.y + dx;
			//if (nx < location.x + SCROLLBUTTONSIZE)
			//	nx = location.x + SCROLLBUTTONSIZE;
			//if (nx > location.x + size.width - SCROLLBUTTONSIZE*2 - buttonBar->getSize().width)
			//	nx = location.x + size.width - SCROLLBUTTONSIZE*2 - buttonBar->getSize().width;
			
			nx-=(location.y + SCROLLBUTTONSIZE);
			
			pp_int32 d = (size.height - buttonBar->getSize().height - SCROLLBUTTONSIZE*2);
			
			if (d != 0)
				pos = nx*65536 / d;
		}
		
		setBarPosition(pos);
		// Call parent event listener
		PPEvent e(eBarPosChanged);
		return eventListener->handleEvent(reinterpret_cast<PPObject*>(this), &e);
	}
	
	return 0;
}

void PPScrollbar::setLocation(PPPoint location)
{
	PPControl::setLocation(location);
	
	delete backgroundButton;	
	delete buttonUp;
	delete buttonDown;
	delete buttonBar;

	initButtons();
}

void PPScrollbar::setSize(pp_uint32 size)
{
	PPPoint buttonDownPos, buttonBarPos;
	PPSize buttonBarSize;
	
	if (horizontal)
	{
		this->size.height = SCROLLBUTTONSIZE;
		this->size.width = size;
	
		buttonDownPos = PPPoint(location.x + size - SCROLLBUTTONSIZE, location.y);
	
		buttonBarPos = PPPoint(location.x + SCROLLBUTTONSIZE, location.y);
	
		buttonBarSize = PPSize((size - SCROLLBUTTONSIZE*2), SCROLLBUTTONSIZE);  
	}
	else
	{
		this->size.width = SCROLLBUTTONSIZE;
		this->size.height = size;
		
		buttonDownPos = PPPoint(location.x, location.y + size - SCROLLBUTTONSIZE);
		
		buttonBarPos = PPPoint(location.x, location.y + SCROLLBUTTONSIZE);
		
		buttonBarSize = PPSize(SCROLLBUTTONSIZE, (size - SCROLLBUTTONSIZE*2));  
	}

	backgroundButton->setLocation(location);
	backgroundButton->setSize(this->size);

	buttonUp->setLocation(location);

	buttonDown->setLocation(buttonDownPos);
}
