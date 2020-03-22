#include <MyGUI_RenderManager.h>
#include "MPImageBox.hpp"

namespace Gui
{
    void MPImageBox::setPropertyRaw(const std::string& _key, const std::string& _value) {
        if (_key == "ImageTexture") {
            mTexture = _value;
            updateTexture();
        }
        else if (_key == "TextureRect")
        {
            mTextureRect = MyGUI::IntCoord::parse(_value);
            mUseWholeTexture = (mTextureRect == MyGUI::IntCoord(0, 0, 0, 0));
            updateTexture();
        }
        else {
            ImageBox::setPropertyOverride(_key, _value);
            MPWidget::setPropertyRaw(_key, _value);
        }
    }

    void MPImageBox::updateTexture() {
        if (!mUseWholeTexture)
        {
            float scale = 1.f;
            MyGUI::ITexture* texture = MyGUI::RenderManager::getInstance().getTexture(mTexture);
            if (texture && getHeight() != 0)
                scale = ((float)texture->getHeight()) / getHeight();

            setImageTile(MyGUI::IntSize(mTextureRect.width * scale, mTextureRect.height * scale));
            MyGUI::IntCoord scaledSize(mTextureRect.left * scale, mTextureRect.top * scale,
                mTextureRect.width * scale, mTextureRect.height * scale);
            setImageCoord(scaledSize);
        }
        if (!mTexture.empty()) setImageTexture(mTexture);
    }
}
