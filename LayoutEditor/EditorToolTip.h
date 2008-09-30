/*!
	@file
	@author		Georgiy Evmenov
	@date		08/2008
	@module
*/
#ifndef __EDITOR_TOOL_TIP_H__
#define __EDITOR_TOOL_TIP_H__

#include <MyGUI.h>
#include "BaseLayout.h"

class EditorToolTip : public BaseLayout
{
public:
	EditorToolTip();

	virtual void initialise();

	void show(const Ogre::UTFString & _text, const MyGUI::IntPoint & _point);
	void show(MyGUI::WidgetPtr _sender, const MyGUI::IntPoint & _point);
	void hide();

private:
	void setPosition(const MyGUI::IntPoint & _point);
	MyGUI::EditPtr mText;

	int minWidth;
	int minHeight;
	MyGUI::WidgetPtr lastWidget;
};

#endif // __EDITOR_TOOL_TIP_H__
