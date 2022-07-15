#include "Theseus.h"
#include "w32Caption.h"

VOID Win32::Caption::AddCaptionButton(CaptionButton* button)
{
    m_CaptionButtons.push_back(button);

}

VOID Win32::Caption::AddCaptionButtonProp(CaptionButton* button)
{
    m_CaptionButtonsProp.push_back(button);
    
}
