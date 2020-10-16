import { Component } from '@angular/core';
import { NavController, NavParams  } from 'ionic-angular';
import * as $ from 'jquery';
import { AlertController } from 'ionic-angular';

@Component({
  selector: 'page-about',
  templateUrl: 'about.html',
})


export class AboutPage {
  unit: any;
  constructor(public navCtrl: NavController, public navParams: NavParams, public atrCtrl: AlertController) {
    console.log(this.navParams.get('data'));
    this.unit = navParams.get('data');
    this.getAssets();
  }

  showAlert(name) {
    let alert = this.atrCtrl.create({
      title: 'Basic Alert!',
      subTitle: 'Button: ' + name,
      buttons: ['OK']
    });
    //alert.present();
  }

  getAssets(){
    $.getJSON("https://api.trackunit.com/public/unit?token=4a1d306f1e7a413d9c933fa1df06bbd3&format=json&id=" + this.unit, function(result){
      $(".ion-list-li").remove("ion-item-group");
      $.each(result, function(i, asset){
        $(".ion-list-li").append("<ion-item-group></ion-item-group>")
        $.each(asset, function(j, fields){
          var assetObj = $.parseJSON(JSON.stringify(fields));
          $("ion-item-group").append("<ion-item-divider color=light>GSE Daten vom "+ assetObj.name +"</ion-item-divider>");
          
          $("ion-item-group").append("<ion-item-divider color=light>Address: "+ JSON.stringify(assetObj.address) + "</ion-item-divider>");
          $("ion-item-group").append("<ion-item-divider color=light>Betriebssunden: "
          + JSON.stringify(assetObj.input1) + " Gesamt: " +  JSON.stringify(assetObj.run1)
          + "</ion-item-divider>");
          $("ion-item-group").append("<p>" + JSON.stringify(assetObj.input1) + "</p>");
          $("ion-item-group").append("<ion-item-divider color=light>Zündung:</ion-item-divider>");
          $("ion-item-group").append("<p>" + JSON.stringify(assetObj.input2) + "</p>");
          $("ion-item-group").append("<ion-item-divider color=light>20% Batterieverbrauch:</ion-item-divider>");
          $("ion-item-group").append("<p>" + JSON.stringify(assetObj.input3) + "</p>");
          $("ion-item-group").append("<ion-item-divider color=light>Lastbetrieb:</ion-item-divider>");
          $("ion-item-group").append("<p>" + JSON.stringify(assetObj.input4) + "</p>");
        });
      });
    });
  }
}
