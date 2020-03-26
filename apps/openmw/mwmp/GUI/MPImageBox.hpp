#pragma once
#include "MPBase.hpp"
#include <MyGUI_ImageBox.h>
#ifndef OPENMW_MPIMAGEBOX_HPP
#define OPENMW_MPIMAGEBOX_HPP

namespace Gui
{
    class MPImageBox : 
        public MyGUI::ImageBox, 
        public MPBase
    {
        MYGUI_RTTI_DERIVED(MPImageBox)
        MP_DERIVED(MPImageBox)
        public:
            static const std::string TEXT_CHANGE;
            static const std::string SELECT_ACCEPT;

            MPImageBox(): ImageBox(), MPBase(), mUseWholeTexture(1) {
                MPBase::initializeWidget(this);
            }

        protected:
            MyGUI::IntCoord mTextureRect;
            bool mUseWholeTexture;
            void setPropertyRaw(const std::string& _key, const std::string& _value);
            std::string mTexture;
            void updateTexture();
    };
}
#endif //OPENMW_MPIMAGEBOX_HPP
