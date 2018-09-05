package com.mcal.ICPE.activity;

import android.app.*;
import android.content.*;
import android.graphics.*;
import android.os.*;
import android.support.v7.widget.*;
import android.view.*;
import android.widget.*;
import com.mcal.ICPE.R;
import android.preference.*;
import com.mcal.moddedpe.*;

public class GuideActivity extends Activity
	{
		private boolean firstLoaded;
		private CheckBox checkBox;
		@Override
		public void onCreate ( Bundle savedInstanceState )
			{
				super.onCreate ( savedInstanceState );

				SharedPreferences preferences=getSharedPreferences ( "ICPE_INFO", Context.MODE_MULTI_PROCESS );
				firstLoaded = preferences.getBoolean ( "first_loaded", false ) && preferences.getString ( "last_version", "" ).equals ( getString ( R.string.app_version ) );

				if ( firstLoaded )
					setContentView ( R.layout.start_activity );
				else
					setContentView ( R.layout.guide_activity );

				WindowManager windowManager = getWindowManager ( );
				Display display = windowManager.getDefaultDisplay ( );
				int screenSize = Math.min ( display.getWidth ( ), display.getHeight ( ) );

				if ( !firstLoaded )
					{
						AppCompatTextView btn=(AppCompatTextView)findViewById ( R.id.guideactivity_UserLegal );
						btn.getPaint ( ).setFlags ( Paint.UNDERLINE_TEXT_FLAG );
						btn.setEnabled ( false );
					}

				checkBox = findViewById ( R.id.guideactivityCheckBox );

				ViewGroup.LayoutParams param = ( (ImageView)findViewById ( firstLoaded ?R.id.startactivityImageView: R.id.guideactivityImageView ) ).getLayoutParams ( );
				param.height = param.width = screenSize / 3;

				if ( !firstLoaded )
					new Thread ( new ListenerLoopRunnable ( ) ).start ( );
				else
					new Thread ( new TimeCounterLoopRunnable ( ) ).start ( );
			}

		public void onAgreeLicense ( View view )
			{
				if ( checkBox.isChecked ( ) )
					{
						SharedPreferences.Editor editor = getSharedPreferences ( "ICPE_INFO", Context.MODE_MULTI_PROCESS ).edit ( );
						editor.putBoolean ( "first_loaded", true );
						editor.putString ( "last_version", getString ( R.string.app_version ) );
						editor.commit ( );
						startActivity ( new Intent ( this, GuideActivity.class ) );
						finish ( );
					}
			}

		public void onReadLicense ( View view )
			{
				Intent intent=new Intent ( this, com.mcal.ICPE.activity.LicenseActivity.class );
				startActivity ( intent );
			}

		private Handler handler = new Handler ( )
			{
				@Override
				public void handleMessage ( Message msg )
					{
						super.handleMessage ( msg );
						if ( checkBox.isChecked ( ) )
							( (AppCompatButton)findViewById ( R.id.guideactivityButtonRectangle ) ).setEnabled ( true );
						else
							( (AppCompatButton)findViewById ( R.id.guideactivityButtonRectangle ) ).setEnabled ( false );

					}
			};

		public class ListenerLoopRunnable implements Runnable
			{
				@Override
				public void run ( )
					{
						while ( true )
							{
								try
									{
										Thread.sleep ( 250 );
										Message msg = new Message ( );
										msg.what = 1;
										handler.sendMessage ( msg );
									}
								catch (InterruptedException e)
									{
										e.printStackTrace ( );
									}
							}
					}
			}

		public class TimeCounterLoopRunnable implements Runnable
			{
				@Override
				public void run ( )
					{
						try
							{
								ModdedPEApplication.instance.init ( );
								com.mcal.ModdedPE.ModdedPEApplication.instance.startLauncher ( GuideActivity.this );
								finish ( );
							}
						catch (Exception e)
							{

							}
					}
			}
	}
