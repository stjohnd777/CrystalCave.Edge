LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES :=  $(LOCAL_PATH)/hellocpp/main.cpp \
$(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
$(LOCAL_PATH)/../../../Classes/BaseLayer.cpp  \
$(LOCAL_PATH)/../../../Classes/CtrlLayer.cpp  \
$(LOCAL_PATH)/../../../Classes/FailedScene.cpp  \
$(LOCAL_PATH)/../../../Classes/FileOperation.cpp  \
$(LOCAL_PATH)/../../../Classes/FontManager.cpp  \
$(LOCAL_PATH)/../../../Classes/Friendly.cpp    \
$(LOCAL_PATH)/../../../Classes/GameLayer.cpp  \
$(LOCAL_PATH)/../../../Classes/GameObject.cpp  \
$(LOCAL_PATH)/../../../Classes/GameSceneManager.cpp   \
$(LOCAL_PATH)/../../../Classes/GLFence.cpp   \
$(LOCAL_PATH)/../../../Classes/GLHorzFence.cpp \
$(LOCAL_PATH)/../../../Classes/GLVertFence.cpp  \
$(LOCAL_PATH)/../../../Classes/HudLayer.cpp   \
$(LOCAL_PATH)/../../../Classes/LabelManager.cpp  \
$(LOCAL_PATH)/../../../Classes/Ligthning.cpp   \
$(LOCAL_PATH)/../../../Classes/LunarModule.cpp  \
$(LOCAL_PATH)/../../../Classes/Mine.cpp      \
$(LOCAL_PATH)/../../../Classes/OptionLayer.cpp  \
$(LOCAL_PATH)/../../../Classes/PersistenceManager.cpp      \
$(LOCAL_PATH)/../../../Classes/Projectile.cpp       \
$(LOCAL_PATH)/../../../Classes/Properties.cpp  \
$(LOCAL_PATH)/../../../Classes/StringUtils.cpp  \
$(LOCAL_PATH)/../../../Classes/SuccessLayer.cpp \
$(LOCAL_PATH)/../../../Classes/TargetObject.cpp \
$(LOCAL_PATH)/../../../Classes/Utils.cpp    \
$(LOCAL_PATH)/../../../Classes/WellcomeScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d)
$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
