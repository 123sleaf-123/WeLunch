cmake_minimum_required(VERSION 3.5)

project(ordering_managment_system VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS Sql REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        restaurant.h restaurant.cpp
        systemdatabase.h systemdatabase.cpp
        logindialog.h logindialog.cpp logindialog.ui
        signupdialog.h signupdialog.cpp signupdialog.ui
        findpwddialog.h findpwddialog.cpp findpwddialog.ui
        changepwddialog.h changepwddialog.cpp changepwddialog.ui
        user_toolbar.h user_toolbar.cpp user_toolbar.ui
        ordercard.h ordercard.cpp ordercard.ui
        foodinordercard.h foodinordercard.cpp foodinordercard.ui
        widget.h widget.cpp widget.ui
        foodinordercardimagebutton.h foodinordercardimagebutton.cpp
        orderlistwidegt.h orderlistwidegt.cpp orderlistwidegt.ui
        orderlistviewcontroller.h orderlistviewcontroller.cpp orderlistviewcontroller.ui
        foodinordercardtextbutton.h foodinordercardtextbutton.cpp
        orderwidget.h orderwidget.cpp orderwidget.ui
        foodshopwidegt.h foodshopwidegt.cpp foodshopwidegt.ui
        foodshopwidgetlinkedlistdeal.h foodshopwidgetlinkedlistdeal.cpp
        FoodShopWidgetOrderByScore.h FoodShopWidgetOrderByScore.cpp
        drcard.h drcard.cpp drcard.ui
        OrderByDistance.cpp OrderByDistance.h
        structDRNode.h
        drwidget.h drwidget.cpp drwidget.ui
        foodindrwidget.h foodindrwidget.cpp foodindrwidget.ui
        AddComment.h AddComment.cpp AddComment.ui
        peopleinformation.h peopleinformation.cpp peopleinformation.ui
        orderdetails.h orderdetails.cpp orderdetails.ui
        foodinformation.cpp foodinformation.h foodinformation.ui
        resaurantinformation.h
        resaurantinformation.cpp
        resaurantinformation.ui
        smartorder.cpp smartorder.h
        ordersubmitreceive.h ordersubmitreceive.cpp ordersubmitreceive.ui
        paywidget.h paywidget.cpp paywidget.ui
        cart.h cart.cpp cart.ui
        captcha.h captcha.cpp
        cartcard.h cartcard.cpp cartcard.ui
        foodinmycart.h foodinmycart.cpp foodinmycart.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ordering_managment_system
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(ordering_managment_system SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(ordering_managment_system
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ordering_managment_system PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(ordering_managment_system PRIVATE Qt${QT_VERSION_MAJOR}::Sql)

set_target_properties(ordering_managment_system PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ordering_managment_system)
endif()
