import { Component } from '@angular/core';
import { AlertController, NavController, NavParams, Platform, ActionSheetController} from 'ionic-angular';
import { AboutPage } from '../about/about';
import { Observable } from 'rxjs/Observable';
import { HomePage } from '../home/home';

declare function executeRequest(number: number): any;
@Component({
  selector: 'page-gse',
  templateUrl: 'gse.html'
})
export class GSEPage {
  response: Observable<any>;
  constructor(public navCtrl: NavController, public navParams: NavParams, public platform: Platform
    , public actionSheetController: ActionSheetController, public atrCtrl: AlertController) {
  }

  
  gotoInfo(param){
    this.navCtrl.push(AboutPage, {
      data: param
    });
  }

  openMenu(unit){
    let actionSheet = this.actionSheetController.create({
      title: 'Unit: ' + unit,
      cssClass: 'action-sheets-basic-page',
      buttons: [
        {
          text: 'Steuern',
          icon: "game-controller-b",
          handler: () => {
            executeRequest(0);

            /*let alert = this.atrCtrl.create({
              title: 'Basic Alert!',
              subTitle: 'Response: ' ,
              buttons: ['OK']
            });
            alert.present();*/
            this.navCtrl.push(HomePage, {
              datas: unit
            });
          }
        },
        {
          text: 'Abbrechen',
          role: 'cancel',
          icon: 'close',
          handler: () => {}
        }
      ]
    });
    actionSheet.present();
  }
}