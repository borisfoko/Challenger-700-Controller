import { NgModule, ErrorHandler } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { IonicApp, IonicModule, IonicErrorHandler } from 'ionic-angular';
import { SmartController } from './app.component';

import { AboutPage } from '../pages/about/about';
import { GSEPage } from '../pages/gse/gse';
import { HomePage } from '../pages/home/home';
import { TabsPage } from '../pages/tabs/tabs';

import { StatusBar } from '@ionic-native/status-bar';
import { SplashScreen } from '@ionic-native/splash-screen';

import { ScreenOrientation } from '@ionic-native/screen-orientation';
import { AndroidFullScreen } from '@ionic-native/android-full-screen';

import { LongPressModule } from  'ionic-long-press';

@NgModule({
  declarations: [
    SmartController,
    AboutPage,
    HomePage,
    GSEPage,
    TabsPage,
  ],
  imports: [
    BrowserModule,
    LongPressModule,
    IonicModule.forRoot(SmartController)
  ],
  bootstrap: [IonicApp,
  ],
  entryComponents: [
    SmartController,
    AboutPage,
    HomePage,
    GSEPage,
    TabsPage
  ],
  providers: [
    StatusBar,
    SplashScreen,
    {provide: ErrorHandler, useClass: IonicErrorHandler},
    ScreenOrientation,
    AndroidFullScreen,
  ]
})
export class AppModule {}
