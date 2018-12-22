#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

// Do we want to showcase direct JNI/NDK interaction?
// Undefine this to get real cross-platform code.
// Uncomment this to try JNI access; this seems to be broken in latest NDKs
#define USE_JNI

#if defined(USE_JNI)
// These headers are only needed for direct NDK/JDK interaction
#include <jni.h>
#include <android/native_activity.h>
#include <android/api-level.h>

// Since we want to get the native activity from SFML, we'll have to use an
// extra header here:
#include <SFML/System/NativeActivity.hpp>
#include <sys/system_properties.h>
#include <android/log.h>

#include <memory>

using std::atoi;

bool isApiLevelHigherThanAndroidO() {
    char apiLevelCharData[PROP_VALUE_MAX+1];
    __system_property_get("ro.build.version.sdk", apiLevelCharData);

    int apiLevel = atoi(apiLevelCharData);

    __android_log_print(ANDROID_LOG_INFO, "API LEVEL IN C++", "%d", apiLevel);

    return apiLevel >= __ANDROID_API_O__;
}


// NDK/JNI sub example - call Java code from native code
int vibrate(sf::Time duration)
{
    // First we'll need the native activity handle
    ANativeActivity *activity = sf::getNativeActivity();

    // Retrieve the JVM and JNI environment
    JavaVM* vm = activity->vm;
    JNIEnv* env = activity->env;

    // First, attach this thread to the main thread
    JavaVMAttachArgs attachargs;
    attachargs.version = JNI_VERSION_1_6;
    attachargs.name = "NativeThread";
    attachargs.group = NULL;
    jint res = vm->AttachCurrentThread(&env, &attachargs);

    if (res == JNI_ERR)
        return EXIT_FAILURE;

    // Retrieve class information
    jclass natact = env->FindClass("android/app/NativeActivity");
    jclass context = env->FindClass("android/content/Context");

    // Get the value of a constant
    jfieldID fid = env->GetStaticFieldID(context, "VIBRATOR_SERVICE", "Ljava/lang/String;");
    jobject svcstr = env->GetStaticObjectField(context, fid);

    // Get the method 'getSystemService' and call it
    jmethodID getss = env->GetMethodID(natact, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
    jobject jVibrator = env->CallObjectMethod(activity->clazz, getss, svcstr);
    jclass class_Vibrator = env->GetObjectClass(jVibrator);

    // Determine the timeframe
    jlong length = duration.asMilliseconds();

    bool apiLevelHigherThanAndroidO = isApiLevelHigherThanAndroidO();

    if(apiLevelHigherThanAndroidO){
        jclass class_VibrationEffect = env->FindClass("android/os/VibrationEffect");

        jmethodID VibrationEffect_createOneShot = env->GetStaticMethodID(class_VibrationEffect, "createOneShot", "(JI)Landroid/os/VibrationEffect;");
        jfieldID VibrationEffect_DEFAULT_AMPLITUDE_ID = env->GetStaticFieldID(class_VibrationEffect, "DEFAULT_AMPLITUDE", "I");
        jint VibrationEffect_DEFAULT_AMPLITUDE = env->GetStaticIntField(class_VibrationEffect, VibrationEffect_DEFAULT_AMPLITUDE_ID);

        jobject VibrationEffect_object = env->CallStaticObjectMethod(class_VibrationEffect, VibrationEffect_createOneShot, length, VibrationEffect_DEFAULT_AMPLITUDE);

        jmethodID vibrate = env->GetMethodID(class_Vibrator, "vibrate","(Landroid/os/VibrationEffect;)V");
        env->CallVoidMethod(jVibrator, vibrate, VibrationEffect_object);

        env->DeleteLocalRef(VibrationEffect_object);
        env->DeleteLocalRef(class_VibrationEffect);
    } else {
        jmethodID vibrate = env->GetMethodID(class_Vibrator, "vibrate","(J)V");

        env->CallVoidMethod(jVibrator, vibrate, length);
    }

    // Free references
    env->DeleteLocalRef(jVibrator);
    env->DeleteLocalRef(class_Vibrator);
    env->DeleteLocalRef(svcstr);
    env->DeleteLocalRef(context);
    env->DeleteLocalRef(natact);

    // Detach thread again
    vm->DetachCurrentThread();

    return EXIT_SUCCESS;
}
#endif

// This is the actual Android example. You don't have to write any platform
// specific code, unless you want to use things not directly exposed.
// ('vibrate()' in this example; undefine 'USE_JNI' above to disable it)
int main(int argc, char *argv[])
{
    sf::VideoMode screen(sf::VideoMode::getDesktopMode());

    sf::RenderWindow window(screen, "");
    window.setFramerateLimit(30);

    sf::Texture texture;
    if(!texture.loadFromFile("image.png"))
        return EXIT_FAILURE;

    sf::Sprite image(texture);
    image.setPosition(screen.width / 2, screen.height / 2);
    image.setOrigin(texture.getSize().x/2, texture.getSize().y/2);

    sf::Font font;
    if (!font.loadFromFile("sansation.ttf"))
        return EXIT_FAILURE;

    sf::Text text("Tap anywhere to move the logo.", font, 64);
    text.setFillColor(sf::Color::Black);
    text.setPosition(10, 10);

    sf::View view = window.getDefaultView();

    sf::Color background = sf::Color::White;

    // We shouldn't try drawing to the screen while in background
    // so we'll have to track that. You can do minor background
    // work, but keep battery life in mind.
    bool active = true;

    while (window.isOpen())
    {
        sf::Event event;

        while (active ? window.pollEvent(event) : window.waitEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();
                    break;
                case sf::Event::Resized:
                    view.setSize(event.size.width, event.size.height);
                    view.setCenter(event.size.width/2, event.size.height/2);
                    window.setView(view);
                    break;
                case sf::Event::LostFocus:
                    background = sf::Color::Black;
                    break;
                case sf::Event::GainedFocus:
                    background = sf::Color::White;
                    break;

                // On Android MouseLeft/MouseEntered are (for now) triggered,
                // whenever the app loses or gains focus.
                case sf::Event::MouseLeft:
                    active = false;
                    break;
                case sf::Event::MouseEntered:
                    active = true;
                    break;
                case sf::Event::TouchBegan:
                    if (event.touch.finger == 0)
                    {
                        image.setPosition(event.touch.x, event.touch.y);
#if defined(USE_JNI)
                        vibrate(sf::milliseconds(1000));
#endif
                    }
                    break;
                default:
                    break;
            }
        }

        if (active)
        {
            window.clear(background);
            window.draw(image);
            window.draw(text);
            window.display();
        }
        else {
            sf::sleep(sf::milliseconds(100));
        }
    }
}
