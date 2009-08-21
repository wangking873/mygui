/*!
	@file
	@author		Albert Semenov
	@date		08/2009
	@module
*/
#ifndef __GRAPH_NODE_SKELETON_STATE_H__
#define __GRAPH_NODE_SKELETON_STATE_H__

#include <MyGUI.h>
#include "BaseAnimationNode.h"
#include "SkeletonState.h"

namespace demo
{

	class GraphNodeSkeletonState : public BaseAnimationNode
	{
	public:
		GraphNodeSkeletonState(const std::string& _name) :
			BaseAnimationNode("GraphNodeSkeletonState.layout"),
			mName(_name),
			mStartIn(nullptr),
			mStopIn(nullptr),
			mPositionIn(nullptr),
			mWeightIn(nullptr)
		{
		}

	private:
		virtual void initialise()
		{
			mMainWidget->setCaption(mName);
			assignBase(mStartIn, "StartIn");
			assignBase(mStopIn, "StopIn");
			assignBase(mPositionIn, "PositionIn");
			assignBase(mWeightIn, "WeightIn");
			assignWidget(mComboStates, "ComboStates");
			assignWidget(mWeightValue, "WeightValue");
			assignWidget(mPositionValue, "PositionValue");
			assignWidget(mStartValue, "StartValue");
			assignWidget(mStopValue, "StopValue");

			mComboStates->eventComboAccept = MyGUI::newDelegate(this, &GraphNodeSkeletonState::notifyComboAccept);
			MyGUI::Gui::getInstance().eventFrameStart += MyGUI::newDelegate(this, &GraphNodeSkeletonState::notifyFrameStart);
		}

		virtual void shutdown()
		{
			MyGUI::Gui::getInstance().eventFrameStart -= MyGUI::newDelegate(this, &GraphNodeSkeletonState::notifyFrameStart);
		}

		void notifyFrameStart(float _time)
		{
			animation::SkeletonState* state = dynamic_cast<animation::SkeletonState*>(getAnimationNode());
			if (state)
			{
				{
					float value = state->getWeight();
					std::ostringstream stream;
					stream.setf(std::ios::fixed, std::ios::floatfield);
					stream.precision(1);
					stream << value;
					mWeightValue->setCaption(stream.str());
				}
				{
					float value = state->getPosition();
					std::ostringstream stream;
					stream.setf(std::ios::fixed, std::ios::floatfield);
					stream.precision(1);
					stream << value;
					mPositionValue->setCaption(stream.str());
				}

				const MyGUI::Colour colour(1, 1, 1);

				if (state->isEnabled())
				{
					mStartValue->setTextColour(colour);
					mStopValue->setTextColour(MyGUI::Colour::Black);
				}
				else
				{
					mStartValue->setTextColour(MyGUI::Colour::Black);
					mStopValue->setTextColour(colour);
				}
			}
		}

		virtual void baseInitialiseAnimationNode()
		{
			Ogre::Any any = getAnimationNode()->getGraph()->getData("OwnerEntity");
			if (!any.isEmpty())
			{
				Ogre::Entity* entity = Ogre::any_cast<Ogre::Entity*>(any);
				Ogre::AnimationStateSet* set = entity->getAllAnimationStates();
				Ogre::AnimationStateIterator iter = set->getAnimationStateIterator();
				while (iter.hasMoreElements())
				{ 
					Ogre::AnimationState* state = iter.getNext(); 
					mComboStates->addItem(state->getAnimationName());
				}
			}

			if (mComboStates->getItemCount() > 0)
			{
				mComboStates->setItemSelectedAt(0);
				notifyComboAccept(mComboStates, 0);
			}
		}

		void notifyComboAccept(MyGUI::ComboBoxPtr _sender, size_t _index)
		{
			if (_index != -1)
				getAnimationNode()->setProperty("StateName", _sender->getItemNameAt(_index));
		}

	private:
		std::string mName;
		wraps::BaseGraphConnection * mStartIn;
		wraps::BaseGraphConnection * mStopIn;
		wraps::BaseGraphConnection * mPositionIn;
		wraps::BaseGraphConnection * mWeightIn;
		MyGUI::ComboBoxPtr mComboStates;
		MyGUI::StaticTextPtr mWeightValue;
		MyGUI::StaticTextPtr mPositionValue;
		MyGUI::StaticTextPtr mStartValue;
		MyGUI::StaticTextPtr mStopValue;

	};

} // namespace demo

#endif // __GRAPH_NODE_SKELETON_STATE_H__
