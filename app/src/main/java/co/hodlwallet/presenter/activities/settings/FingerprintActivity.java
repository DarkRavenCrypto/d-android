package co.hodlwallet.presenter.activities.settings;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.text.SpannableString;
import android.text.Spanned;
import android.text.TextPaint;
import android.text.method.LinkMovementMethod;
import android.text.style.ClickableSpan;
import android.util.Log;
import android.view.View;
import android.widget.CompoundButton;
import android.widget.ImageButton;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.ToggleButton;

import co.hodlwallet.R;
import co.hodlwallet.presenter.activities.util.ActivityUTILS;
import co.hodlwallet.presenter.activities.util.BRActivity;
import co.hodlwallet.presenter.customviews.BRDialogView;
import co.hodlwallet.presenter.interfaces.BRAuthCompletion;
import co.hodlwallet.tools.animation.BRAnimator;
import co.hodlwallet.tools.animation.BRDialog;
import co.hodlwallet.tools.manager.BRSharedPrefs;
import co.hodlwallet.tools.security.AuthManager;
import co.hodlwallet.tools.security.BRKeyStore;
import co.hodlwallet.tools.util.BRConstants;
import co.hodlwallet.tools.util.BRCurrency;
import co.hodlwallet.tools.util.BRExchange;
import co.hodlwallet.tools.util.Utils;

import java.math.BigDecimal;


public class FingerprintActivity extends BRActivity {
    private static final String TAG = FingerprintActivity.class.getName();

    public RelativeLayout layout;
    public static boolean appVisible = false;
    private static FingerprintActivity app;
    private TextView limitExchange;
    private TextView limitInfo;

    private ToggleButton toggleButton;

    public static FingerprintActivity getApp() {
        return app;
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fingerprint);
        toggleButton = (ToggleButton) findViewById(R.id.toggleButton);
        limitExchange = (TextView) findViewById(R.id.limit_exchange);
        limitInfo = (TextView) findViewById(R.id.limit_info);

        ImageButton faq = (ImageButton) findViewById(R.id.faq_button);

        faq.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!BRAnimator.isClickAllowed()) return;
                BRAnimator.showSupportFragment(app, BRConstants.enableFingerprint);
            }
        });

        toggleButton.setChecked(BRSharedPrefs.getUseFingerprint(this));

        limitExchange.setText(getLimitText());

        toggleButton.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                Activity app = FingerprintActivity.this;
                if (isChecked && !Utils.isFingerprintEnrolled(app)) {
                    Log.e(TAG, "onCheckedChanged: fingerprint not setup");
                    BRDialog.showCustomDialog(app, getString(R.string.TouchIdSettings_disabledWarning_title_android), getString(R.string.TouchIdSettings_disabledWarning_body_android), getString(R.string.Button_ok), null, new BRDialogView.BROnClickListener() {
                        @Override
                        public void onClick(BRDialogView brDialogView) {
                            brDialogView.dismissWithAnimation();
                        }
                    }, null, null, 0);
                    buttonView.setChecked(false);
                } else {
                    BRSharedPrefs.putUseFingerprint(app, isChecked);
                }

            }
        });
        SpannableString ss = new SpannableString(getString(R.string.TouchIdSettings_customizeText_android));
        ClickableSpan clickableSpan = new ClickableSpan() {
            @Override
            public void onClick(View textView) {

                AuthManager.getInstance().authPrompt(FingerprintActivity.this, null, getString(R.string.VerifyPin_continueBody), true, false, new BRAuthCompletion() {
                    @Override
                    public void onComplete() {
                        Intent intent = new Intent(FingerprintActivity.this, SpendLimitActivity.class);
                        overridePendingTransition(R.anim.enter_from_right, R.anim.exit_to_left);
                        startActivity(intent);
                        finish();
                    }

                    @Override
                    public void onCancel() {

                    }
                });


            }

            @Override
            public void updateDrawState(TextPaint ds) {
                super.updateDrawState(ds);
                ds.setUnderlineText(false);
                ds.setColor(getColor(R.color.logo_gradient_start));
            }
        };
        // make the whole text clickable if failed to select the last word
        ss.setSpan(clickableSpan, limitInfo.getText().toString().indexOf("\u200B"), limitInfo.getText().toString().lastIndexOf("\u200B"), Spanned.SPAN_EXCLUSIVE_EXCLUSIVE);

        limitInfo.setText(ss);
        limitInfo.setMovementMethod(LinkMovementMethod.getInstance());
        limitInfo.setHighlightColor(Color.TRANSPARENT);

    }

    private String getLimitText() {
        String iso = BRSharedPrefs.getIso(this);
        //amount in satoshis
        BigDecimal satoshis = new BigDecimal(BRKeyStore.getSpendLimit(this));
        //amount in BTC, mBTC or bits
        BigDecimal amount = BRExchange.getAmountFromSatoshis(this, BRConstants.bitcoinUppercase, satoshis);
        //amount in user preferred ISO (e.g. USD)
        BigDecimal curAmount = BRExchange.getAmountFromSatoshis(this, iso, satoshis);
        //formatted string for the label
        return String.format(getString(R.string.TouchIdSettings_spendingLimit), BRCurrency.getFormattedCurrencyString(this, BRConstants.bitcoinUppercase, amount), BRCurrency.getFormattedCurrencyString(this, iso, curAmount));
    }

    @Override
    protected void onResume() {
        super.onResume();
        appVisible = true;
        app = this;
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
//        BRAnimator.startBreadActivity(this, false);
        overridePendingTransition(R.anim.enter_from_left, R.anim.exit_to_right);
    }

    @Override
    public void onPause() {
        super.onPause();
        appVisible = false;
    }

}
