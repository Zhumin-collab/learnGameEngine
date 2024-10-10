//
// created by yzm on 2024/10/9
//

#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include <iostream>
#include <string>
#include <functional>

#include "component/component.h"

class UIImage;
class UIButton : public Component {
public:
    UIButton();
    ~UIButton();

    void set_image_normal(UIImage* image) {m_image_normal = image;}
    void set_image_press(UIImage* image) {m_image_press = image;}

    void set_click_callback(std::function<void()> callback) {m_click_callback = callback;}

public:
    void Update() override;

private:

    UIImage* m_image_normal;
    UIImage* m_image_press;
    bool m_press;
    std::function<void()> m_click_callback;

};



#endif //UI_BUTTON_H