package co.hodlwallet.presenter.fragments;

import android.app.Activity;
import android.app.Fragment;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.LayoutRes;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.constraint.ConstraintLayout;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewTreeObserver;
import android.widget.ArrayAdapter;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import co.hodlwallet.R;
import co.hodlwallet.presenter.activities.intro.IntroActivity;
import co.hodlwallet.presenter.activities.settings.NodesActivity;
import co.hodlwallet.presenter.activities.settings.SecurityCenterActivity;
import co.hodlwallet.presenter.activities.settings.SettingsActivity;
import co.hodlwallet.presenter.activities.settings.WebViewActivity;
import co.hodlwallet.presenter.entities.BRMenuItem;
import co.hodlwallet.presenter.interfaces.BROnSignalCompletion;
import co.hodlwallet.tools.animation.BRAnimator;
import co.hodlwallet.tools.animation.SlideDetector;
import co.platform.APIClient;
import co.platform.HTTPServer;

import java.util.ArrayList;
import java.util.List;

import static co.hodlwallet.R.id.menu_listview;

/**
 * BreadWallet
 * <p>
 * Created by Mihail Gutan <mihail@breadwallet.com> on 6/29/15.
 * Copyright (c) 2016 breadwallet LLC
 * <p>
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * <p>
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * <p>
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

public class FragmentMenu extends Fragment {
    private static final String TAG = FragmentMenu.class.getName();

    public TextView mTitle;
    public ListView mListView;
    public RelativeLayout background;
    public List<BRMenuItem> itemList;
    public ConstraintLayout signalLayout;
    private ImageButton close;


    @Override
    public View onCreateView(LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {
        // The last two arguments ensure LayoutParams are inflated
        // properly.

        View rootView = inflater.inflate(R.layout.fragment_menu, container, false);
        background = (RelativeLayout) rootView.findViewById(R.id.layout);
        signalLayout = (ConstraintLayout) rootView.findViewById(R.id.signal_layout);
        background.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!BRAnimator.isClickAllowed()) return;
                getActivity().onBackPressed();
            }
        });

        close = (ImageButton) rootView.findViewById(R.id.close_button);

        itemList = new ArrayList<>();

        itemList.add(new BRMenuItem(getString(R.string.MenuButton_security), new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Activity app = getActivity();
                Intent intent = new Intent(app, SecurityCenterActivity.class);
                app.startActivity(intent);
                app.overridePendingTransition(R.anim.enter_from_bottom, R.anim.fade_down);
            }
        }));
        itemList.add(new BRMenuItem(getString(R.string.MenuButton_support), new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!BRAnimator.isClickAllowed()) return;
                BRAnimator.showSupportFragment(getActivity(), null);
            }
        }));
        itemList.add(new BRMenuItem(getString(R.string.MenuButton_settings), new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getActivity(), SettingsActivity.class);
                Activity app = getActivity();
                app.startActivity(intent);
                app.overridePendingTransition(R.anim.enter_from_bottom, R.anim.fade_down);
            }
        }));
        itemList.add(new BRMenuItem(getString(R.string.MenuButton_lock), new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                final Activity from = getActivity();
                from.getFragmentManager().popBackStack();
                BRAnimator.startBreadActivity(from, true);
            }
        }));

        close.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Activity app = getActivity();
                if (app != null)
                    app.getFragmentManager().popBackStack();
            }
        });
        mTitle = rootView.findViewById(R.id.title);
        mListView = rootView.findViewById(menu_listview);
        mListView.setAdapter(new MenuListAdapter(getContext(), R.layout.menu_list_item, itemList));

        return rootView;
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        final ViewTreeObserver observer = mListView.getViewTreeObserver();
        observer.addOnGlobalLayoutListener(new ViewTreeObserver.OnGlobalLayoutListener() {
            @Override
            public void onGlobalLayout() {
                observer.removeGlobalOnLayoutListener(this);
                BRAnimator.animateBackgroundDim(background, false);
                BRAnimator.animateSignalSlide(signalLayout, false, null);
            }
        });
    }

    public class MenuListAdapter extends ArrayAdapter<BRMenuItem> {

        private Context mContext;
        private int defaultLayoutResource = R.layout.menu_list_item;

        public MenuListAdapter(@NonNull Context context, @LayoutRes int resource, @NonNull List<BRMenuItem> items) {
            super(context, resource, items);
            this.mContext = context;
        }

        @NonNull
        @Override
        public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
            if (convertView == null) {
                // inflate the background
                LayoutInflater inflater = ((Activity) mContext).getLayoutInflater();
                convertView = inflater.inflate(defaultLayoutResource, parent, false);
            }
            TextView text = (TextView) convertView.findViewById(R.id.item_text);

            text.setText(getItem(position).text);
            convertView.setOnClickListener(getItem(position).listener);
            return convertView;

        }

        @Override
        public int getCount() {
            return super.getCount();
        }
    }

    @Override
    public void onStop() {
        super.onStop();
        BRAnimator.animateBackgroundDim(background, true);
        BRAnimator.animateSignalSlide(signalLayout, true, new BRAnimator.OnSlideAnimationEnd() {
            @Override
            public void onAnimationEnd() {
                if (getActivity() != null)
                    getActivity().getFragmentManager().popBackStack();
            }
        });

    }

    @Override
    public void onResume() {
        super.onResume();

    }

    @Override
    public void onPause() {
        super.onPause();
    }

}
