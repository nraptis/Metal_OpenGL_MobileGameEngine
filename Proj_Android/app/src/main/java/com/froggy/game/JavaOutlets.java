package com.froggy.game;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;

import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.locks.ReentrantLock;

import java.util.concurrent.*;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.media.MediaPlayer;
import android.provider.Settings;
import android.util.Log;

public class JavaOutlets
{
	private static Context mContext;
	private static MediaPlayer mMusicPlayer;
	private static GL2JNIView mOpenGL;

	private ArrayList<ReentrantLock> mLockList = new ArrayList<ReentrantLock>(100);
	//private ArrayList<Semaphore> mLockList = new ArrayList<Semaphore>(100);




	//

	public static void setContext(Context c) {
		mContext = c;
	}

	public static void setOpenGL(GL2JNIView glv) {
		mOpenGL = glv;
	}

	public static void PrintMemory() {
		long freeSize = 0L;
		long totalSize = 0L;
		long usedSize = -1L;

		try {
			Runtime info = Runtime.getRuntime();
			freeSize = info.freeMemory();
			totalSize = info.totalMemory();
			usedSize = totalSize - freeSize;
		} catch(Exception e) {
			e.printStackTrace();
		}

		double aPercent = 1.0f;

		if (totalSize > 20) {
			aPercent = (double)usedSize / (double)totalSize;
		}

		aPercent = aPercent * 100;

		Log.d("java", "**Memory Free = [" + freeSize + " / " + totalSize
				+ "] => " + (aPercent) + "% Free\n\n");

	}

	public void commitRender() {
		if (mOpenGL != null) {
			mOpenGL.requestRender();
		}

	}

	public int getAssetScale() {
		int aResult = 0;
		if (mContext != null) {

			float aDensity = mContext.getResources().getDisplayMetrics().density;

			if (aDensity < 1.95f) {
				aResult = (int)(aDensity + 0.75);
			} else {
				aResult = (int)(aDensity + 0.25);
			}

			Log.d("java", "Raw Scale = " + mContext.getResources().getDisplayMetrics().density);
			Log.d("java", "Chosen Scale = " + aResult);

		}
		return aResult;
	}


	public int createThreadLock() {
		int aResult = mLockList.size();

		ReentrantLock aLock = new ReentrantLock();
		mLockList.add(aLock);

		//Lock aLock = new Lock();
		//mLockList.add(aLock);

		//Semaphore aLock = new Semaphore(1);
		//mLockList.add(aLock);




		return aResult;
	}

	public boolean doesThreadLockExist(int pLockIndex) {
		if (pLockIndex >= 0 && pLockIndex < mLockList.size()) {
			return true;
		}
		return false;
	}

	public void lockThread(int pLockIndex) {
		if (pLockIndex >= 0 && pLockIndex < mLockList.size()) {


			//
			/*
			try {
				mLockList.get(pLockIndex).acquire();
			} catch (InterruptedException exc) {
				Log.d("java", "*****************");
				Log.d("java", "BAD SEMAPHORE!!!!!!!");
				System.out.println(exc);
			}
			*/

			try {
				mLockList.get(pLockIndex).lock();
			} catch (IllegalMonitorStateException exc) {
				Log.d("java", "*****************");
				Log.d("java", "BAD LOCK!!!!!!!");
				System.out.println(exc);

			}
		}
	}

	public void unlockThread(int pLockIndex) {
		if (pLockIndex >= 0 && pLockIndex < mLockList.size()) {

			//mLockList.get(pLockIndex).release();

			try {
				mLockList.get(pLockIndex).unlock();
			} catch (IllegalMonitorStateException exc) {
				Log.d("java", "*****************");
				Log.d("java", "BAD UN-LOCK!!!!!!!");
				System.out.println(exc);
			}

		}
	}

	public void deleteThreadLock(int pLockIndex) {
		if (pLockIndex >= 0 && pLockIndex < mLockList.size()) {

			//mLockList.get(pLockIndex).release();

			try {
				mLockList.get(pLockIndex).unlock();
			} catch (IllegalMonitorStateException exc) {
				Log.d("java", "*****************");
				Log.d("java", "BAD UN-LOCK!!!!!!!");
				System.out.println(exc);
			}


			mLockList.remove(pLockIndex);
		}
	}

	public void deleteAllThreadLocks() {
		for (int i=0;i<mLockList.size();i++) {

			//mLockList.get(i).release();

			try {
				mLockList.get(i).unlock();
			} catch (IllegalMonitorStateException exc) {
				Log.d("java", "*****************");
				Log.d("java", "BAD UN-LOCK!!!!!!!");
				System.out.println(exc);
			}

		}
		mLockList.clear();
	}

	public void JavaLog(String pText) {
		if (pText.length() <= 0)
			pText = " ";
		Log.d("c++", pText);
	}

	public boolean fileExists(String pPath) {
		boolean aReturn = false;
		try {
			InputStream is = mContext.getResources().getAssets().open(pPath);
			int aLength = is.available();
			if(aLength > 0)
			{
				aReturn = true;
			}
			is.close();
		} catch (Exception e) {

		}
		return aReturn;
	}

	public int readFileLength(String pPath) {
		int aReturn = 0;
		try {
			InputStream is = mContext.getResources().getAssets().open(pPath);
			aReturn = is.available();
			is.close();
		} catch (Exception e) {

		}
		if (aReturn == 0) {
			File aFile = new File(pPath);
			try {
				FileInputStream aStream = new FileInputStream(aFile);
				aReturn = aStream.available();
				aStream.close();
			} catch (Exception e) {

			}
		}
		return aReturn;
	}

	public void readFileData(String pPath, byte[] pData) {
		boolean aDidRead = false;
		try {
			InputStream is = mContext.getResources().getAssets().open(pPath);
			int aLength = is.available();
			if(aLength > 0) {
				is.read(pData);
				aDidRead = true;
			}
			is.close();
		}
		catch (Exception e) {

		}

		if(aDidRead == false) {
			File aFile = new File(pPath);
			try {
				FileInputStream aStream = new FileInputStream(aFile);
				int aLength = aStream.available();

				if (aLength > 0) {
					aStream.read(pData);
					aDidRead = true;
				}
				aStream.close();
			} catch (Exception e) {

			}
		}
	}

	public boolean writeFileData(String pPath, byte[] pData, int pLength) {
		boolean aReturn = false;

		String aString = pData.toString();

		try {
			File aFile = new File(pPath);// mContext.getDir("saved", Context.MODE_PRIVATE);
			if (aFile.exists() == false) {
				aFile.createNewFile();
				aFile.mkdir();

			}

			FileOutputStream fos = new FileOutputStream(aFile);
			fos.write(pData);
			fos.close();
			aReturn = true;
		}
		catch (Exception e)
		{
			Log.d("java", "Save File Exception!" + e);
		}
		return aReturn;
	}

	/*
	private Bitmap scaleBitmap(Bitmap bitmapToScale, float newWidth, float newHeight)
	{
		if (bitmapToScale == null)
		{
			return null;
		}

		int width = bitmapToScale.getWidth();
		int height = bitmapToScale.getHeight();

		Matrix matrix = new Matrix();

		// resize the bit map
		matrix.postScale(newWidth / width, newHeight / height);

		// recreate the new Bitmap and set it back
		return Bitmap.createBitmap(bitmapToScale, 0, 0, bitmapToScale.getWidth(), bitmapToScale.getHeight(), matrix,
				true);
	}


	public Bitmap openBitmap(String path, boolean iScalePOT)
	{
		Bitmap bitmap = null;
		try
		{
			//BitmapFactory.Options options = new BitmapFactory.Options();
			//options.inSampleSize = 1;
			//bm = BitmapFactory.decodeFile(myImagePath, options);



			bitmap = BitmapFactory.decodeStream(mContext.getResources().getAssets().open(path));

			if(iScalePOT)
			{
				int originalWidth = getBitmapWidth(bitmap);
				int originalHeight = getBitmapHeight(bitmap);
				int width = nextPOT(originalWidth);
				int height = nextPOT(originalHeight);
				if (originalWidth != width || originalHeight != height)
				{
					bitmap = scaleBitmap(bitmap, width, height);
				}
			}

		}
		catch (Exception e)
		{
			// Log.w("NDKHelper", "Coundn't load a file:" + path);
		}

		return bitmap;
	}
	*/

	public Bitmap loadBitmap(String path)
	{
		Bitmap bitmap = null;
		try
		{
			bitmap = BitmapFactory.decodeStream(mContext.getResources().getAssets().open(path));
		}
		catch (Exception e)
		{
			//Log.w("NDKHelper", "Couldn't load a file:" + path);
		}

		return bitmap;
	}



	public int getBitmapWidth(Bitmap bmp)
	{
		return bmp.getWidth();
	}

	public int getBitmapHeight(Bitmap bmp)
	{
		return bmp.getHeight();
	}

	public void getBitmapPixels(Bitmap bmp, int[] pixels)
	{
		int w = bmp.getWidth();
		int h = bmp.getHeight();

		bmp.getPixels(pixels, 0, w, 0, 0, w, h);


		/*
		int aLength = pixels.length;

		int aColor;


		for (int i = 0; i < aLength; i++)
		{
			aColor = pixels[i];

			int aAlpha = (((aColor) >> 24) & 0xFF);
			int aRed = (((aColor) >> 16) & 0xFF);
			int aGreen = (((aColor) >> 8) & 0xFF);
			int aBlue = (((aColor)) & 0xFF);

			pixels[i] = ((((int) aAlpha) << 24) & 0xFF000000)
					| ((((int) aGreen) << 8) & 0x0000FF00)
					| ((((int) aBlue) << 16) & 0x00FF0000)
					| ((((int) aRed)) & 0x000000FF);

			// pixels[i] = aColor;
		}

		*/

	}

	public void closeBitmap(Bitmap bmp)
	{
		bmp.recycle();
	}



	/*
	public int loadSound(String pPath, int pInstanceCount)
	{
		int aReturn = 0;

		Log.d("java", "LOADING SOUND [" + pPath + "]" + "Inst["
				+ pInstanceCount + "]");

		AssetManager aAssetManager = context.getResources().getAssets();

		try {
			InputStream is = aAssetManager.open(pPath);

			int aLength = is.available();
			if (aLength > 0) {
				Log.d("java", "Loaded Sound! [" + pPath + "]" + "("
						+ aLength + ")");
				aReturn = 1;
			}

			is.close();
		} catch (Exception e) {

		}

		return aReturn;
	}
	*/


	/*

	public static String getNativeLibraryDirectory(Context appContext) {

		 * ApplicationInfo ai = context.getApplicationInfo();
		 *
		 * Log.w("NDKHelper", "ai.nativeLibraryDir:" + ai.nativeLibraryDir);
		 *
		 * if ((ai.flags & ApplicationInfo.FLAG_UPDATED_SYSTEM_APP) != 0 ||
		 * (ai.flags & ApplicationInfo.FLAG_SYSTEM) == 0) { return
		 * ai.nativeLibraryDir; }


		return "/system/lib/";
	}

	*/


	public AssetManager getAssetManager() {
		AssetManager aAssetManager = mContext.getResources().getAssets();
		return aAssetManager;
	}

	//

	//public static native void setAssetManager(AssetManager assetManager);
	//public static native boolean createMusicPlayer(AssetManager assetManager, String filename);
	//public static native boolean setMusicPlaying(boolean pPlaying);

}
