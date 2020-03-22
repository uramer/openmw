#pragma once
#include "MPWidget.hpp"
#include <MyGUI_ImageBox.h>
#ifndef OPENMW_MPIMAGEBOX_HPP
#define OPENMW_MPIMAGEBOX_HPP

namespace Gui
{
    class MPImageBox : 
        public MyGUI::ImageBox, 
        public MPWidget
    {
        MYGUI_RTTI_DERIVED(MPImageBox)
        MP_DERIVED(MPImageBox)
        public:
            static const std::string TEXT_CHANGE;
            static const std::string SELECT_ACCEPT;

            MPImageBox(): ImageBox(), MPWidget(), mUseWholeTexture(1) {
                MPWidget::initialize(this);
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
