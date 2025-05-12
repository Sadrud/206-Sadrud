set(CMAKE_C_COMPILER "/usr/lib64/ccache/cc")
set(CMAKE_C_COMPILER_ARG1 "")
set(CMAKE_C_COMPILER_ID "GNU")
set(CMAKE_C_COMPILER_VERSION "9.2.1")
set(CMAKE_C_COMPILER_VERSION_INTERNAL "")
set(CMAKE_C_COMPILER_WRAPPER "")
set(CMAKE_C_STANDARD_COMPUTED_DEFAULT "99")
set(CMAKE_C_COMPILE_FEATURES "c_std_90;c_function_prototypes;c_std_99;c_restrict;c_variadic_macros;c_std_11;c_static_assert")
set(CMAKE_C90_COMPILE_FEATURES "c_std_90;c_function_prototypes")
set(CMAKE_C99_COMPILE_FEATURES "c_std_99;c_restrict;c_variadic_macros")
set(CMAKE_C11_COMPILE_FEATURES "c_std_11;c_static_assert")

set(CMAKE_C_PLATFORM_ID "Linux")
set(CMAKE_C_SIMULATE_ID "")
set(CMAKE_C_SIMULATE_VERSION "")



set(CMAKE_AR "/usr/bin/ar")
set(CMAKE_C_COMPILER_AR "/usr/bin/gcc-ar")
set(CMAKE_RANLIB "/usr/bin/ranlib")
set(CMAKE_C_COMPILER_RANLIB "/usr/bin/gcc-ranlib")
set(CMAKE_LINKER "/usr/bin/ld")
set(CMAKE_MT "")
set(CMAKE_COMPILER_IS_GNUCC 1)
set(CMAKE_C_COMPILER_LOADED 1)
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_C_ABI_COMPILED TRUE)
set(CMAKE_COMPILER_IS_MINGW )
set(CMAKE_COMPILER_IS_CYGWIN )
if(CMAKE_COMPILER_IS_CYGWIN)
  set(CYGWIN 1)
  set(UNIX 1)
endif()

set(CMAKE_C_COMPILER_ENV_VAR "CC")

if(CMAKE_COMPILER_IS_MINGW)
  set(MINGW 1)
endif()
set(CMAKE_C_COMPILER_ID_RUN 1)
set(CMAKE_C_SOURCE_FILE_EXTENSIONS c;m)
set(CMAKE_C_IGNORE_EXTENSIONS h;H;o;O;obj;OBJ;def;DEF;rc;RC)
set(CMAKE_C_LINKER_PREFERENCE 10)

# Save compiler ABI information.
set(CMAKE_C_SIZEOF_DATA_PTR "8")
set(CMAKE_C_COMPILER_ABI "ELF")
set(CMAKE_C_LIBRARY_ARCHITECTURE "")

if(CMAKE_C_SIZEOF_DATA_PTR)
  set(CMAKE_SIZEOF_VOID_P "${CMAKE_C_SIZEOF_DATA_PTR}")
endif()

if(CMAKE_C_COMPILER_ABI)
  set(CMAKE_INTERNAL_PLATFORM_ABI "${CMAKE_C_COMPILER_ABI}")
endif()

if(CMAKE_C_LIBRARY_ARCHITECTURE)
  set(CMAKE_LIBRARY_ARCHITECTURE "")
endif()

set(CMAKE_C_CL_SHOWINCLUDES_PREFIX "")
if(CMAKE_C_CL_SHOWINCLUDES_PREFIX)
  set(CMAKE_CL_SHOWINCLUDES_PREFIX "${CMAKE_C_CL_SHOWINCLUDES_PREFIX}")
endif()





set(CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES "/usr/include/qt5;/usr/include/qt5/Qt3DQuickScene2D;/usr/include/qt5/Qt3DQuickScene2D/5.12.4;/usr/include/qt5/Qt3DQuickScene2D/5.12.4/Qt3DQuickScene2D;/usr/include/qt5/Qt3DQuickScene2D/5.12.4/Qt3DQuickScene2D/private;/usr/include/qt5/QtNetwork;/usr/include/qt5/QtNetwork/5.12.4;/usr/include/qt5/QtNetwork/5.12.4/QtNetwork;/usr/include/qt5/QtInputSupport;/usr/include/qt5/QtInputSupport/5.12.4;/usr/include/qt5/QtInputSupport/5.12.4/QtInputSupport;/usr/include/qt5/QtPacketProtocol;/usr/include/qt5/QtPacketProtocol/5.12.4;/usr/include/qt5/QtPacketProtocol/5.12.4/QtPacketProtocol;/usr/include/qt5/QtPacketProtocol/5.12.4/QtPacketProtocol/private;/usr/include/qt5/QtXcb;/usr/include/qt5/QtSerialPort;/usr/include/qt5/QtSerialPort/5.12.4;/usr/include/qt5/QtSerialPort/5.12.4/QtSerialPort;/usr/include/qt5/QtSerialPort/5.12.4/QtSerialPort/private;/usr/include/qt5/QtEdidSupport;/usr/include/qt5/QtEdidSupport/5.12.4;/usr/include/qt5/QtEdidSupport/5.12.4/QtEdidSupport;/usr/include/qt5/QtWebKitWidgets;/usr/include/qt5/QtWebKitWidgets/5.212.0;/usr/include/qt5/QtWebKitWidgets/5.212.0/QtWebKitWidgets;/usr/include/qt5/QtWebKitWidgets/5.212.0/QtWebKitWidgets/private;/usr/include/qt5/Qt3DCore;/usr/include/qt5/Qt3DCore/5.12.4;/usr/include/qt5/Qt3DCore/5.12.4/Qt3DCore;/usr/include/qt5/Qt3DCore/5.12.4/Qt3DCore/private;/usr/include/qt5/Enginio;/usr/include/qt5/Enginio/1.6.2;/usr/include/qt5/Enginio/1.6.2/Enginio;/usr/include/qt5/Enginio/1.6.2/Enginio/private;/usr/include/qt5/QtFbSupport;/usr/include/qt5/QtFbSupport/5.12.4;/usr/include/qt5/QtFbSupport/5.12.4/QtFbSupport;/usr/include/qt5/QtFbSupport/5.12.4/QtFbSupport/private;/usr/include/qt5/QtXmlPatterns;/usr/include/qt5/QtXmlPatterns/5.12.4;/usr/include/qt5/QtXmlPatterns/5.12.4/QtXmlPatterns;/usr/include/qt5/QtXmlPatterns/5.12.4/QtXmlPatterns/private;/usr/include/qt5/QtMultimediaQuick;/usr/include/qt5/QtMultimediaQuick/5.12.4;/usr/include/qt5/QtMultimediaQuick/5.12.4/QtMultimediaQuick;/usr/include/qt5/QtMultimediaQuick/5.12.4/QtMultimediaQuick/private;/usr/include/qt5/Qt3DQuickRender;/usr/include/qt5/Qt3DQuickRender/5.12.4;/usr/include/qt5/Qt3DQuickRender/5.12.4/Qt3DQuickRender;/usr/include/qt5/Qt3DQuickRender/5.12.4/Qt3DQuickRender/private;/usr/include/qt5/QtMultimediaGstTools;/usr/include/qt5/Qt3DQuickExtras;/usr/include/qt5/Qt3DQuickExtras/5.12.4;/usr/include/qt5/Qt3DQuickExtras/5.12.4/Qt3DQuickExtras;/usr/include/qt5/Qt3DQuickExtras/5.12.4/Qt3DQuickExtras/private;/usr/include/qt5/QtEventDispatcherSupport;/usr/include/qt5/QtEventDispatcherSupport/5.12.4;/usr/include/qt5/QtEventDispatcherSupport/5.12.4/QtEventDispatcherSupport;/usr/include/qt5/QtEventDispatcherSupport/5.12.4/QtEventDispatcherSupport/private;/usr/include/qt5/QtUiPlugin;/usr/include/qt5/Qt3DQuick;/usr/include/qt5/Qt3DQuick/5.12.4;/usr/include/qt5/Qt3DQuick/5.12.4/Qt3DQuick;/usr/include/qt5/Qt3DQuick/5.12.4/Qt3DQuick/private;/usr/include/qt5/QtPlatformCompositorSupport;/usr/include/qt5/QtPlatformCompositorSupport/5.12.4;/usr/include/qt5/QtPlatformCompositorSupport/5.12.4/QtPlatformCompositorSupport;/usr/include/qt5/QtPlatformCompositorSupport/5.12.4/QtPlatformCompositorSupport/private;/usr/include/qt5/QtConcurrent;/usr/include/qt5/Qt3DRender;/usr/include/qt5/Qt3DRender/5.12.4;/usr/include/qt5/Qt3DRender/5.12.4/Qt3DRender;/usr/include/qt5/Qt3DRender/5.12.4/Qt3DRender/private;/usr/include/qt5/Qt3DLogic;/usr/include/qt5/Qt3DLogic/5.12.4;/usr/include/qt5/Qt3DLogic/5.12.4/Qt3DLogic;/usr/include/qt5/Qt3DLogic/5.12.4/Qt3DLogic/private;/usr/include/qt5/QtQuickWidgets;/usr/include/qt5/QtQuickWidgets/5.12.4;/usr/include/qt5/QtQuickWidgets/5.12.4/QtQuickWidgets;/usr/include/qt5/QtQuickWidgets/5.12.4/QtQuickWidgets/private;/usr/include/qt5/Qt3DInput;/usr/include/qt5/Qt3DInput/5.12.4;/usr/include/qt5/Qt3DInput/5.12.4/Qt3DInput;/usr/include/qt5/Qt3DInput/5.12.4/Qt3DInput/private;/usr/include/qt5/QtCore;/usr/include/qt5/QtCore/5.12.4;/usr/include/qt5/QtCore/5.12.4/QtCore;/usr/include/qt5/QtScript;/usr/include/qt5/QtScript/5.12.4;/usr/include/qt5/QtScript/5.12.4/QtScript;/usr/include/qt5/QtScript/5.12.4/QtScript/private;/usr/include/qt5/QtWebKit;/usr/include/qt5/QtWebKit/5.212.0;/usr/include/qt5/QtWebKit/5.212.0/QtWebKit;/usr/include/qt5/QtWebKit/5.212.0/QtWebKit/private;/usr/include/qt5/QtMultimedia;/usr/include/qt5/QtMultimedia/5.12.4;/usr/include/qt5/QtMultimedia/5.12.4/QtMultimedia;/usr/include/qt5/QtMultimedia/5.12.4/QtMultimedia/private;/usr/include/qt5/QtEglSupport;/usr/include/qt5/QtEglSupport/5.12.4;/usr/include/qt5/QtEglSupport/5.12.4/QtEglSupport;/usr/include/qt5/QtEglSupport/5.12.4/QtEglSupport/private;/usr/include/qt5/QtQml;/usr/include/qt5/QtQml/5.12.4;/usr/include/qt5/QtQml/5.12.4/QtQml;/usr/include/qt5/QtQml/5.12.4/QtQml/private;/usr/include/qt5/QtWaylandClient;/usr/include/qt5/QtWaylandClient/5.12.4;/usr/include/qt5/QtWaylandClient/5.12.4/QtWaylandClient;/usr/include/qt5/QtWaylandClient/5.12.4/QtWaylandClient/private;/usr/include/qt5/QtKmsSupport;/usr/include/qt5/QtKmsSupport/5.12.4;/usr/include/qt5/QtKmsSupport/5.12.4/QtKmsSupport;/usr/include/qt5/QtKmsSupport/5.12.4/QtKmsSupport/private;/usr/include/qt5/Qt3DExtras;/usr/include/qt5/Qt3DExtras/5.12.4;/usr/include/qt5/Qt3DExtras/5.12.4/Qt3DExtras;/usr/include/qt5/Qt3DExtras/5.12.4/Qt3DExtras/private;/usr/include/qt5/QtGui;/usr/include/qt5/QtGui/5.12.4;/usr/include/qt5/QtGui/5.12.4/QtGui;/usr/include/qt5/QtGui/5.12.4/QtGui/qpa;/usr/include/qt5/QtSvg;/usr/include/qt5/QtSvg/5.12.4;/usr/include/qt5/QtSvg/5.12.4/QtSvg;/usr/include/qt5/QtSvg/5.12.4/QtSvg/private;/usr/include/qt5/QtTest;/usr/include/qt5/QtTest/5.12.4;/usr/include/qt5/QtTest/5.12.4/QtTest;/usr/include/qt5/QtAccessibilitySupport;/usr/include/qt5/QtAccessibilitySupport/5.12.4;/usr/include/qt5/QtAccessibilitySupport/5.12.4/QtAccessibilitySupport;/usr/include/qt5/QtAccessibilitySupport/5.12.4/QtAccessibilitySupport/private;/usr/include/qt5/QtQuick;/usr/include/qt5/QtQuick/5.12.4;/usr/include/qt5/QtQuick/5.12.4/QtQuick;/usr/include/qt5/QtQuick/5.12.4/QtQuick/private;/usr/include/qt5/QtXml;/usr/include/qt5/QtXml/5.12.4;/usr/include/qt5/QtXml/5.12.4/QtXml;/usr/include/qt5/QtX11Extras;/usr/include/qt5/QtBluetooth;/usr/include/qt5/QtBluetooth/5.12.4;/usr/include/qt5/QtBluetooth/5.12.4/QtBluetooth;/usr/include/qt5/QtBluetooth/5.12.4/QtBluetooth/private;/usr/include/qt5/QtLocation;/usr/include/qt5/QtLocation/5.12.4;/usr/include/qt5/QtLocation/5.12.4/QtLocation;/usr/include/qt5/QtLocation/5.12.4/QtLocation/private;/usr/include/qt5/QtWebChannel;/usr/include/qt5/QtWebChannel/5.12.4;/usr/include/qt5/QtWebChannel/5.12.4/QtWebChannel;/usr/include/qt5/QtWebChannel/5.12.4/QtWebChannel/private;/usr/include/qt5/QtDeviceDiscoverySupport;/usr/include/qt5/QtDeviceDiscoverySupport/5.12.4;/usr/include/qt5/QtDeviceDiscoverySupport/5.12.4/QtDeviceDiscoverySupport;/usr/include/qt5/QtDeviceDiscoverySupport/5.12.4/QtDeviceDiscoverySupport/private;/usr/include/qt5/QtQmlDebug;/usr/include/qt5/QtQmlDebug/5.12.4;/usr/include/qt5/QtQmlDebug/5.12.4/QtQmlDebug;/usr/include/qt5/QtQmlDebug/5.12.4/QtQmlDebug/private;/usr/include/qt5/QtThemeSupport;/usr/include/qt5/QtThemeSupport/5.12.4;/usr/include/qt5/QtThemeSupport/5.12.4/QtThemeSupport;/usr/include/qt5/QtThemeSupport/5.12.4/QtThemeSupport/private;/usr/include/qt5/QtQuickTest;/usr/include/qt5/QtQuickTest/5.12.4;/usr/include/qt5/QtQuickTest/5.12.4/QtQuickTest;/usr/include/qt5/QtQuickTest/5.12.4/QtQuickTest/private;/usr/include/qt5/QtQuickParticles;/usr/include/qt5/QtQuickParticles/5.12.4;/usr/include/qt5/QtQuickParticles/5.12.4/QtQuickParticles;/usr/include/qt5/QtQuickParticles/5.12.4/QtQuickParticles/private;/usr/include/qt5/QtDBus;/usr/include/qt5/QtDBus/5.12.4;/usr/include/qt5/QtDBus/5.12.4/QtDBus;/usr/include/qt5/QtSensors;/usr/include/qt5/QtSensors/5.12.4;/usr/include/qt5/QtSensors/5.12.4/QtSensors;/usr/include/qt5/QtSensors/5.12.4/QtSensors/private;/usr/include/qt5/QtPlatformHeaders;/usr/include/qt5/QtGlxSupport;/usr/include/qt5/QtGlxSupport/5.12.4;/usr/include/qt5/QtGlxSupport/5.12.4/QtGlxSupport;/usr/include/qt5/QtGlxSupport/5.12.4/QtGlxSupport/private;/usr/include/qt5/QtQuickShapes;/usr/include/qt5/QtQuickShapes/5.12.4;/usr/include/qt5/QtQuickShapes/5.12.4/QtQuickShapes;/usr/include/qt5/QtQuickShapes/5.12.4/QtQuickShapes/private;/usr/include/qt5/QtLinuxAccessibilitySupport;/usr/include/qt5/QtLinuxAccessibilitySupport/5.12.4;/usr/include/qt5/QtLinuxAccessibilitySupport/5.12.4/QtLinuxAccessibilitySupport;/usr/include/qt5/QtLinuxAccessibilitySupport/5.12.4/QtLinuxAccessibilitySupport/private;/usr/include/qt5/QtServiceSupport;/usr/include/qt5/QtServiceSupport/5.12.4;/usr/include/qt5/QtServiceSupport/5.12.4/QtServiceSupport;/usr/include/qt5/QtServiceSupport/5.12.4/QtServiceSupport/private;/usr/include/qt5/QtPrintSupport;/usr/include/qt5/QtPrintSupport/5.12.4;/usr/include/qt5/QtPrintSupport/5.12.4/QtPrintSupport;/usr/include/qt5/QtPrintSupport/5.12.4/QtPrintSupport/qpa;/usr/include/qt5/Qt3DQuickInput;/usr/include/qt5/Qt3DQuickInput/5.12.4;/usr/include/qt5/Qt3DQuickInput/5.12.4/Qt3DQuickInput;/usr/include/qt5/Qt3DQuickInput/5.12.4/Qt3DQuickInput/private;/usr/include/qt5/QtDesigner;/usr/include/qt5/QtDesigner/5.12.4;/usr/include/qt5/QtDesigner/5.12.4/QtDesigner;/usr/include/qt5/QtDesigner/5.12.4/QtDesigner/private;/usr/include/qt5/QtWebSockets;/usr/include/qt5/QtWebSockets/5.12.4;/usr/include/qt5/QtWebSockets/5.12.4/QtWebSockets;/usr/include/qt5/QtWebSockets/5.12.4/QtWebSockets/private;/usr/include/qt5/QtWaylandCompositor;/usr/include/qt5/QtWaylandCompositor/5.12.4;/usr/include/qt5/QtWaylandCompositor/5.12.4/QtWaylandCompositor;/usr/include/qt5/QtWaylandCompositor/5.12.4/QtWaylandCompositor/private;/usr/include/qt5/QtNfc;/usr/include/qt5/QtNfc/5.12.4;/usr/include/qt5/QtNfc/5.12.4/QtNfc;/usr/include/qt5/QtNfc/5.12.4/QtNfc/private;/usr/include/qt5/QtScriptTools;/usr/include/qt5/QtScriptTools/5.12.4;/usr/include/qt5/QtScriptTools/5.12.4/QtScriptTools;/usr/include/qt5/QtScriptTools/5.12.4/QtScriptTools/private;/usr/include/qt5/QtOpenGLExtensions;/usr/include/qt5/Qt3DAnimation;/usr/include/qt5/Qt3DAnimation/5.12.4;/usr/include/qt5/Qt3DAnimation/5.12.4/Qt3DAnimation;/usr/include/qt5/Qt3DAnimation/5.12.4/Qt3DAnimation/private;/usr/include/qt5/QtOpenGL;/usr/include/qt5/QtOpenGL/5.12.4;/usr/include/qt5/QtOpenGL/5.12.4/QtOpenGL;/usr/include/qt5/Qt3DQuickAnimation;/usr/include/qt5/Qt3DQuickAnimation/5.12.4;/usr/include/qt5/Qt3DQuickAnimation/5.12.4/Qt3DQuickAnimation;/usr/include/qt5/Qt3DQuickAnimation/5.12.4/Qt3DQuickAnimation/private;/usr/include/qt5/QtEglFSDeviceIntegration;/usr/include/qt5/QtEglFSDeviceIntegration/5.12.4;/usr/include/qt5/QtEglFSDeviceIntegration/5.12.4/QtEglFSDeviceIntegration;/usr/include/qt5/QtDesignerComponents;/usr/include/qt5/QtDesignerComponents/5.12.4;/usr/include/qt5/QtDesignerComponents/5.12.4/QtDesignerComponents;/usr/include/qt5/QtDesignerComponents/5.12.4/QtDesignerComponents/private;/usr/include/qt5/QtPositioning;/usr/include/qt5/QtPositioning/5.12.4;/usr/include/qt5/QtPositioning/5.12.4/QtPositioning;/usr/include/qt5/QtPositioning/5.12.4/QtPositioning/private;/usr/include/qt5/QtSql;/usr/include/qt5/QtSql/5.12.4;/usr/include/qt5/QtSql/5.12.4/QtSql;/usr/include/qt5/QtUiTools;/usr/include/qt5/QtUiTools/5.12.4;/usr/include/qt5/QtUiTools/5.12.4/QtUiTools;/usr/include/qt5/QtUiTools/5.12.4/QtUiTools/private;/usr/include/qt5/QtFontDatabaseSupport;/usr/include/qt5/QtFontDatabaseSupport/5.12.4;/usr/include/qt5/QtFontDatabaseSupport/5.12.4/QtFontDatabaseSupport;/usr/include/qt5/QtFontDatabaseSupport/5.12.4/QtFontDatabaseSupport/private;/usr/include/qt5/QtPositioningQuick;/usr/include/qt5/QtPositioningQuick/5.12.4;/usr/include/qt5/QtPositioningQuick/5.12.4/QtPositioningQuick;/usr/include/qt5/QtPositioningQuick/5.12.4/QtPositioningQuick/private;/usr/include/qt5/QtMultimediaWidgets;/usr/include/qt5/QtMultimediaWidgets/5.12.4;/usr/include/qt5/QtMultimediaWidgets/5.12.4/QtMultimediaWidgets;/usr/include/qt5/QtMultimediaWidgets/5.12.4/QtMultimediaWidgets/private;/usr/include/qt5/QtHelp;/usr/include/qt5/QtHelp/5.12.4;/usr/include/qt5/QtHelp/5.12.4/QtHelp;/usr/include/qt5/QtHelp/5.12.4/QtHelp/private;/usr/include/qt5/QtWidgets;/usr/include/qt5/QtWidgets/5.12.4;/usr/include/qt5/QtWidgets/5.12.4/QtWidgets;/usr/local/intel/impi/5.1.3.223/intel64/include;/usr/lib/gcc/x86_64-redhat-linux/9/include;/usr/local/include;/usr/include")
set(CMAKE_C_IMPLICIT_LINK_LIBRARIES "gcc;gcc_s;c;gcc;gcc_s;m;stdc++;gcc_s")
set(CMAKE_C_IMPLICIT_LINK_DIRECTORIES "/usr/lib/gcc/x86_64-redhat-linux/9;/usr/lib64;/lib64;/usr/lib")
set(CMAKE_C_IMPLICIT_LINK_FRAMEWORK_DIRECTORIES "")
