#ifndef Magnum_Platform_WindowlessWindowsEglApplication_h
#define Magnum_Platform_WindowlessWindowsEglApplication_h
/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

/** @file
 * @brief Class @ref Magnum::Platform::WindowlessWindowsEglApplication, macro @ref MAGNUM_WINDOWLESSWINDOWSEGLAPPLICATION_MAIN()
 */

#include <memory>
#ifndef DOXYGEN_GENERATING_OUTPUT
#define WIN32_LEAN_AND_MEAN 1
#define VC_EXTRALEAN
#endif
#include <windows.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <Corrade/Containers/EnumSet.h>

#include "Magnum/Magnum.h"
#include "Magnum/OpenGL.h"
#include "Magnum/Platform/Platform.h"

namespace Magnum { namespace Platform {

/**
@brief Windowless Windows/EGL application

Application for offscreen rendering using pure WINAPI and EGL.

This application library is available on OpenGL ES (also ANGLE) on Windows. It
is built if `WITH_WINDOWLESSWINDOWSEGLAPPLICATION` is enabled in CMake.

## Bootstrap application

Fully contained windowless application using @ref WindowlessWindowsEglApplication
along with CMake setup is available in `windowless` branch of
[Magnum Bootstrap](https://github.com/mosra/magnum-bootstrap) repository,
download it as [tar.gz](https://github.com/mosra/magnum-bootstrap/archive/windowless.tar.gz)
or [zip](https://github.com/mosra/magnum-bootstrap/archive/windowless.zip)
file. After extracting the downloaded archive you can build and run the
application with these four commands:

    mkdir build && cd build
    cmake ..
    cmake --build .
    ./src/MyApplication # or ./src/Debug/MyApplication

See @ref cmake for more information.

## General usage

In CMake you need to request `WindowlessWindowsEglApplication` component of
`Magnum` package and link to `Magnum::WindowlessWindowsEglApplication` target.
If no other windowless application is requested, you can also use generic
`Magnum::WindowlessApplication` alias to simplify porting. Again, see
@ref building and @ref cmake for more information.

Place your code into @ref exec(). The subclass can be then used in main
function using @ref MAGNUM_WINDOWLESSWINDOWSEGLAPPLICATION_MAIN() macro. See
@ref platform for more information.
@code
class MyApplication: public Platform::WindowlessWindowsEglApplication {
    // implement required methods...
};
MAGNUM_WINDOWLESSWINDOWSEGLAPPLICATION_MAIN(MyApplication)
@endcode

If no other application header is included, this class is also aliased to
`Platform::WindowlessApplication` and the macro is aliased to
`MAGNUM_WINDOWLESSAPPLICATION_MAIN()` to simplify porting.
*/
class WindowlessWindowsEglApplication {
    public:
        /** @brief Application arguments */
        struct Arguments {
            /** @brief Constructor */
            /*implicit*/ constexpr Arguments(int& argc, char** argv, HWND window) noexcept: argc{argc}, argv{argv}, window{window} {}

            int& argc;      /**< @brief Argument count */
            char** argv;    /**< @brief Argument values */
            #ifndef DOXYGEN_GENERATING_OUTPUT
            HWND window;
            #endif
        };

        class Configuration;

        #ifndef DOXYGEN_GENERATING_OUTPUT
        static int create(LRESULT(CALLBACK windowProcedure)(HWND, UINT, WPARAM, LPARAM));
        #endif

        /** @copydoc Sdl2Application::Sdl2Application(const Arguments&, const Configuration&) */
        #ifdef DOXYGEN_GENERATING_OUTPUT
        explicit WindowlessWindowsEglApplication(const Arguments& arguments, const Configuration& configuration = Configuration());
        #else
        /* To avoid "invalid use of incomplete type" */
        explicit WindowlessWindowsEglApplication(const Arguments& arguments, const Configuration& configuration);
        explicit WindowlessWindowsEglApplication(const Arguments& arguments);
        #endif

        /** @copydoc Sdl2Application::Sdl2Application(const Arguments&, std::nullptr_t) */
        explicit WindowlessWindowsEglApplication(const Arguments& arguments, std::nullptr_t);

        /** @brief Copying is not allowed */
        WindowlessWindowsEglApplication(const WindowlessWindowsEglApplication&) = delete;

        /** @brief Moving is not allowed */
        WindowlessWindowsEglApplication(WindowlessWindowsEglApplication&&) = delete;

        /** @brief Copying is not allowed */
        WindowlessWindowsEglApplication& operator=(const WindowlessWindowsEglApplication&) = delete;

        /** @brief Moving is not allowed */
        WindowlessWindowsEglApplication& operator=(WindowlessWindowsEglApplication&&) = delete;

        /**
         * @brief Execute application
         * @return Value for returning from `main()`
         *
         * See @ref MAGNUM_WINDOWLESSWINDOWSEGLAPPLICATION_MAIN() for usage
         * information.
         */
        virtual int exec() = 0;

    protected:
        /* Nobody will need to have (and delete) WindowlessWindowsEglApplication*,
           thus this is faster than public pure virtual destructor */
        ~WindowlessWindowsEglApplication();

        /** @copydoc Sdl2Application::createContext() */
        #ifdef DOXYGEN_GENERATING_OUTPUT
        void createContext(const Configuration& configuration = Configuration());
        #else
        /* To avoid "invalid use of incomplete type" */
        void createContext(const Configuration& configuration);
        void createContext();
        #endif

        /** @copydoc Sdl2Application::tryCreateContext() */
        bool tryCreateContext(const Configuration& configuration);

    private:
        HWND _window;
        EGLDisplay _display;
        EGLConfig _config;
        EGLSurface _surface;
        EGLContext _glContext;

        std::unique_ptr<Platform::Context> _context;
};

/**
@brief Configuration

@see @ref WindowlessWindowsEglApplication(), @ref createContext(),
    @ref tryCreateContext()
*/
class WindowlessWindowsEglApplication::Configuration {
    public:
        /**
         * @brief Context flag
         *
         * @see @ref Flags, @ref setFlags(), @ref Context::Flag
         */
        enum class Flag: int {
            Debug = EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR    /**< Create debug context */
        };

        /**
         * @brief Context flags
         *
         * @see @ref setFlags(), @ref Context::Flags
         */
        #ifndef DOXYGEN_GENERATING_OUTPUT
        typedef Containers::EnumSet<Flag, EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR> Flags;
        #else
        typedef Containers::EnumSet<Flag> Flags;
        #endif

        constexpr /*implicit*/ Configuration() {}

        /** @brief Context flags */
        Flags flags() const { return _flags; }

        /**
         * @brief Set context flags
         * @return Reference to self (for method chaining)
         *
         * Default is no flag. See also @ref Context::flags().
         */
        Configuration& setFlags(Flags flags) {
            _flags = flags;
            return *this;
        }

    private:
        Flags _flags;
};

/** @hideinitializer
@brief Entry point for windowless Windows/EGL application
@param className Class name

See @ref Magnum::Platform::WindowlessWindowsEglApplication "Platform::WindowlessWindowsEglApplication"
for usage information. This macro abstracts out platform-specific entry point
code, see @ref portability-applications for more information. When no other
windowless application header is included this macro is also aliased to
`MAGNUM_WINDOWLESSAPPLICATION_MAIN()`.
*/
#define MAGNUM_WINDOWLESSWINDOWSEGLAPPLICATION_MAIN(className)                     \
    int globalArgc; char** globalArgv;                                      \
    LRESULT CALLBACK windowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); \
    LRESULT CALLBACK windowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { \
        switch(message) {                                                   \
            case WM_CREATE:                                                 \
                {                                                           \
                    className app({globalArgc, globalArgv, hWnd});          \
                    PostQuitMessage(app.exec());                            \
                }                                                           \
                break;                                                      \
            default: return DefWindowProc(hWnd, message, wParam, lParam);   \
        }                                                                   \
        return 0;                                                           \
    }                                                                       \
    int main(int argc, char** argv) {                                       \
        globalArgc = argc;                                                  \
        globalArgv = argv;                                                  \
        return Magnum::Platform::WindowlessWindowsEglApplication::create(windowProcedure); \
    }

#ifndef DOXYGEN_GENERATING_OUTPUT
#ifndef MAGNUM_WINDOWLESSAPPLICATION_MAIN
typedef WindowlessWindowsEglApplication WindowlessApplication;
#define MAGNUM_WINDOWLESSAPPLICATION_MAIN(className) MAGNUM_WINDOWLESSWINDOWSEGLAPPLICATION_MAIN(className)
#else
#undef MAGNUM_WINDOWLESSAPPLICATION_MAIN
#endif
#endif

}}

#endif
