package com.froggy.game;


import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.support.v4.view.MotionEventCompat;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.egl.EGLSurface;
import javax.microedition.khronos.opengles.GL10;
import android.opengl.EGL14;
import android.view.View;


class GL2JNIView extends GLSurfaceView {
    private static String TAG = "???";
    private static final boolean DEBUG = false;

    private ContextFactory mFactory;
    private Renderer mRenderer;

    public void SetContext() {
        Log.d("java", "Setting GLContext [" + mFactory + "]");
    }

    public GL2JNIView(Context context) {
        super(context);
        JavaOutlets.setContext(context);
        init(24, 0);
    }

    public GL2JNIView(Context context, int depth, int stencil) {
        super(context);
        init(depth, stencil);
    }

    private void init(int depth, int stencil) {

        Log.d("java", "GL2JNIView -- init(" + depth + ") Sten(" + stencil + ")..");

        //setLayerType(View.LAYER_TYPE_SOFTWARE, null);

        /* Setup the context factory for 2.0 rendering.
         * See ContextFactory class definition below
         */

        setPreserveEGLContextOnPause(true);

        mFactory = new ContextFactory();
        setEGLContextFactory(mFactory );



        /* We need to choose an EGLConfig that matches the format of
         * our surface exactly. This is going to be done in our
         * custom config chooser. See ConfigChooser class definition
         * below.
         */
        setEGLConfigChooser( new ConfigChooser(5, 6, 5, 0, depth, stencil) );
        //
        //setEGLConfigChooser( new ConfigChooser(4, 4, 4, 0, depth, stencil) );


        /* Set the renderer responsible for frame rendering */
        mRenderer = new Renderer();
        setRenderer(mRenderer);

        setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);

    }

    @Override
    public void onPause() {
        //mRenderer.mDidFlagGraphicsReady = false;
        super.onPause();
    }

    @Override
    public void onResume() {
        super.onResume();
    }

    @Override
    public boolean onTouchEvent(MotionEvent e) {
        int aAction = MotionEventCompat.getActionMasked(e);
        int aActionIndex = MotionEventCompat.getActionIndex(e);

        int aPointerCount = MotionEventCompat.getPointerCount(e);

        for (int i = (aPointerCount - 1); i >= 0; i--) {
            // float aX = MotionEventCompat.getX(e, aActionIndex);
            // float aY = MotionEventCompat.getY(e, aActionIndex);

            float aX = MotionEventCompat.getX(e, i);
            float aY = MotionEventCompat.getY(e, i);

            int aIndex = i;

            if (i == aActionIndex) {
                if (aAction == MotionEvent.ACTION_MOVE) {
                    GL2JNILib.NativeAppShellTouchMove(aX, aY, aIndex,
                            aPointerCount);
                } else if (aAction == MotionEvent.ACTION_DOWN || aAction == MotionEvent.ACTION_POINTER_DOWN) {
                    GL2JNILib.NativeAppShellTouchBegin(aX, aY, aIndex, aPointerCount);
                } else if (aAction == MotionEvent.ACTION_UP || aAction == MotionEvent.ACTION_POINTER_UP) {
                    GL2JNILib.NativeAppShellTouchRelease(aX, aY, aIndex, aPointerCount);
                } else if (aAction == MotionEvent.ACTION_CANCEL) {
                    GL2JNILib.NativeAppShellTouchCancel(aX, aY, aIndex, aPointerCount);
                }
            } else {
                GL2JNILib.NativeAppShellTouchMove(aX, aY, aIndex, aPointerCount);
            }
        }
        return true;
    }


    private static class ContextFactory implements GLSurfaceView.EGLContextFactory {
        private static int EGL_CONTEXT_CLIENT_VERSION = 0x3098;

        public EGLContext mContext;

        public EGLContext createContext(EGL10 egl, EGLDisplay display, EGLConfig eglConfig) {
            Log.w(TAG, "creating OpenGL ES 2.0 context");

            checkEglError("Before eglCreateContext", egl);
            int[] aContextAttribs = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL10.EGL_NONE };
            mContext = egl.eglCreateContext(display, eglConfig, EGL10.EGL_NO_CONTEXT, aContextAttribs);
            checkEglError("After eglCreateContext", egl);

            //Might need to reload textures!! LOOL!!
            Log.d("java", "Created OpenGL CONTEXT!!!!!!!\n");

            return mContext;
        }

        public void destroyContext(EGL10 egl, EGLDisplay display, EGLContext context) {
            if (mContext == context) {
                mContext = null;
            }
            egl.eglDestroyContext(display, context);
            Log.d("java", "Destroyed OpenGL CONTEXT!!!!!!!\n");

        }
    }

    private static void checkEglError(String prompt, EGL10 egl) {
        int error;
        while ((error = egl.eglGetError()) != EGL10.EGL_SUCCESS) {
            Log.e(TAG, String.format("%s: EGL error: 0x%x", prompt, error));
        }
    }

    private static class ConfigChooser implements GLSurfaceView.EGLConfigChooser {

        public ConfigChooser(int r, int g, int b, int a, int depth, int stencil) {
            mRedSize = r;
            mGreenSize = g;
            mBlueSize = b;
            mAlphaSize = a;
            mDepthSize = depth;
            mStencilSize = stencil;
        }

        /* This EGL config specification is used to specify 2.0 rendering.
         * We use a minimum size of 4 bits for red/green/blue, but will
         * perform actual matching in chooseConfig() below.
         */
        private static int EGL_OPENGL_ES2_BIT = 4;
        private static int[] s_configAttribs2 =
        {
            EGL10.EGL_RED_SIZE, 4,
            EGL10.EGL_GREEN_SIZE, 4,
            EGL10.EGL_BLUE_SIZE, 4,
            EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL10.EGL_NONE
        };

        public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display) {

            /* Get the number of minimally matching EGL configurations
             */
            int[] num_config = new int[1];
            egl.eglChooseConfig(display, s_configAttribs2, null, 0, num_config);

            int numConfigs = num_config[0];

            if (numConfigs <= 0) {
                throw new IllegalArgumentException("No configs match configSpec");
            }

            EGLConfig[] configs = new EGLConfig[numConfigs];
            egl.eglChooseConfig(display, s_configAttribs2, configs, numConfigs, num_config);

            return chooseConfig(egl, display, configs);
        }

        public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display,
                EGLConfig[] configs) {
            for(EGLConfig config : configs) {
                int d = findConfigAttrib(egl, display, config,
                        EGL10.EGL_DEPTH_SIZE, 0);
                int s = findConfigAttrib(egl, display, config,
                        EGL10.EGL_STENCIL_SIZE, 0);

                // We need at least mDepthSize and mStencilSize bits
                if (d < mDepthSize || s < mStencilSize) continue;

                // We want an *exact* match for red/green/blue/alpha
                int r = findConfigAttrib(egl, display, config,
                        EGL10.EGL_RED_SIZE, 0);
                int g = findConfigAttrib(egl, display, config,
                            EGL10.EGL_GREEN_SIZE, 0);
                int b = findConfigAttrib(egl, display, config,
                            EGL10.EGL_BLUE_SIZE, 0);
                int a = findConfigAttrib(egl, display, config,
                        EGL10.EGL_ALPHA_SIZE, 0);

                if (r == mRedSize && g == mGreenSize && b == mBlueSize && a == mAlphaSize)
                    return config;
            }
            return null;
        }

        private int findConfigAttrib(EGL10 egl, EGLDisplay display,
                EGLConfig config, int attribute, int defaultValue) {

            if (egl.eglGetConfigAttrib(display, config, attribute, mValue)) {
                return mValue[0];
            }
            return defaultValue;
        }

        // Subclasses can adjust these values:
        protected int mRedSize;
        protected int mGreenSize;
        protected int mBlueSize;
        protected int mAlphaSize;
        protected int mDepthSize;
        protected int mStencilSize;
        private int[] mValue = new int[1];
    }

    private static class Renderer implements GLSurfaceView.Renderer {

        private boolean mDidInitialize = false;
        private boolean mDidFlagGraphicsReady = false;

        public void onDrawFrame(GL10 gl) {

            if (mDidInitialize == true && mDidFlagGraphicsReady == false) {
                mDidFlagGraphicsReady = true;
                GL2JNILib.NativeAppShellGraphicsSetUp();
            }

            GL2JNILib.NativeAppShellFrame();
        }

        public void onSurfaceChanged(GL10 gl, int width, int height) {
            Log.d("java", "onSurfaceChanged()!!!!!!!\n");

            if (mDidInitialize  == false) {
                mDidInitialize = true;
                Log.d("java", "onSurfaceChanged() 1st -- GL2JNILib.NativeAppShellInitialize(w:" + width + ", h:" + height + ");\n");
                GL2JNILib.NativeAppShellInitialize(width, height);
            }
        }

        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            Log.d("java", "onSurfaceCreated()!!!!!!!\n");
        }

    }
}
