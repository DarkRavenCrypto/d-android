package co.pford.presenter.activities.intro;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import co.pford.R;
import co.pford.presenter.activities.InputWordsActivity;
import co.pford.presenter.activities.util.ActivityUTILS;
import co.pford.presenter.activities.util.BRActivity;
import co.pford.tools.animation.BRAnimator;
import co.pford.tools.animation.SpringAnimator;

public class RecoverActivity extends BRActivity {
    private Button nextButton;
    public static boolean appVisible = false;
    private static RecoverActivity app;

    public static RecoverActivity getApp() {
        return app;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_intro_recover);

        nextButton = (Button) findViewById(R.id.send_button);

        nextButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!BRAnimator.isClickAllowed()) return;
                Intent intent = new Intent(RecoverActivity.this, InputWordsActivity.class);
                startActivity(intent);
                overridePendingTransition(R.anim.enter_from_right, R.anim.exit_to_left);
            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();
        appVisible = true;
        app = this;
    }

    @Override
    protected void onPause() {
        super.onPause();
        appVisible = false;
    }


    @Override
    public void onBackPressed() {
        super.onBackPressed();
        overridePendingTransition(R.anim.enter_from_left, R.anim.exit_to_right);
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
    }
}
