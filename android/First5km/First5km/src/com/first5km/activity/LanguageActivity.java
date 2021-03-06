package com.first5km.activity;

import com.first5km.R;
import com.first5km.util.Locale;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;

public class LanguageActivity extends Activity {
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.languageactivity);
    }
    
    public void onButtonClick(View view) {
    	if (view.getId() == R.id.selectdanish) {
    		Locale.selectDanish();
    	} else {
    		Locale.selectEnglish();
    	}
    	
		startActivity(new Intent(this, First5kmActivity.class));
    }
}
