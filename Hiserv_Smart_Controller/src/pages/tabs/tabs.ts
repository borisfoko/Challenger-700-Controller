import { Component } from '@angular/core';
import {NavParams, NavController} from 'ionic-angular';

import { GSEPage } from '../gse/gse';
import { AboutPage } from '../about/about';
@Component({
  selector: 'page-tabs',
  templateUrl: 'tabs.html'
})
export class TabsPage {
  private rootPage;

  constructor(public navCtrl: NavController, public navParams: NavParams) {
    this.rootPage = GSEPage;
  }

  gotoGSEPage(){
    console.log("GSE Page");
    this.rootPage = GSEPage;
  }
  gotoAboutPage(){
    this.rootPage = AboutPage;
  }

  /*ionViewDidLoad(){
    this.lockScreenOrientation();
  }*/
}
