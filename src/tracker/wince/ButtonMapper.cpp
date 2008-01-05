#include "TrackerSettingsDatabase.h"
#include "XMFile.h"
#include "PPSystem_WIN32.h"
#include "..\PPUI\Event.h"
#include "ButtonMapper.h"

static TrackerSettingsDatabase* keyDatabase = NULL;

TButtonMapping	mappings[256];

void InitButtonRemapper()
{
	memset(mappings, 0xFF, sizeof(mappings));

	if (XMFile::exists(System::getConfigFileName(_T("keys.cfg"))))
	{
		// load mappings
		keyDatabase = new TrackerSettingsDatabase();	

		XMFile f(System::getConfigFileName(_T("keys.cfg")));

		keyDatabase->serialize(f);

		const PPDictionaryKey* theKey = keyDatabase->getFirstKey();
		
		while (theKey)
		{
			PPString str = theKey->getKey();
			
			if (memcmp(str, "KEY:", 4) == 0)
			{
				unsigned int v = theKey->getIntValue();
				
				DWORD buttonCode = (WORD)(v & 0xFFFF);
				
				if (buttonCode < 256)
				{
					mappings[buttonCode].keyModifiers = (BYTE)(v >> 16);
					mappings[buttonCode].virtualKeyCode = (BYTE)(v >> 24);
				}
			}
			theKey = keyDatabase->getNextKey();
		}

		theKey = keyDatabase->restore("ORIENTATION");
		if (theKey)
		{
			switch (theKey->getIntValue())
			{
				case 0:
					orientation = eOrientation90CW;
					break;

				case 1:
					orientation = eOrientation90CCW;
					break;
				
				case 2:
					orientation = eOrientationNormal;
					break;
			}
		}

		theKey = keyDatabase->restore("ALLOWVIRTUALKEYS");
		if (theKey)
		{
			allowVirtualKeys = theKey->getIntValue();
		}

		theKey = keyDatabase->restore("HIDETASKBAR");
		if (theKey)
		{
			hideTaskBar = theKey->getIntValue();
		}

		theKey = keyDatabase->restore("DOUBLEPIXELS");
		if (theKey)
		{
			doublePixels = theKey->getIntValue();
		}

		theKey = keyDatabase->restore("DONTTURNOFFDEVICE");
		if (theKey)
		{
			dontTurnOffDevice = theKey->getIntValue();
		}

		delete keyDatabase;

	}

}
