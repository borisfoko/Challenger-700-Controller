import { Component } from '@angular/core';
import { AlertController, NavController, NavParams  } from 'ionic-angular';
import nipplejs from 'nipplejs';
import * as $ from 'jquery';

declare function executeRequest(number: number): any;
@Component({
  selector: 'page-home',
  templateUrl: 'home.html'
})
export class HomePage {
  unit: any;
  keyPressed:boolean;
  currentKeyId:any;
  constructor(public navCtrl: NavController, public navParams: NavParams, public atrCtrl: AlertController) {
    console.log(this.navParams.get('datas'));
    this.unit = navParams.get('datas');
    //this.getAssets();
    this.keyPressed = false;
    $.ajaxSetup({timeout:100});
  }
  
  /*getAssets(){
    $.getJSON("https://api.trackunit.com/public/unit?token=4a1d306f1e7a413d9c933fa1df06bbd3&format=json&id=" + this.unit, function(result){
      $.each(result, function(i, asset){
        $.each(asset, function(j, fields){
          var assetObj = $.parseJSON(JSON.stringify(fields));
          $("#GSE_NAME").append("<p>" + assetObj.name + "</p>");
          $("#E2").append("<p>" + JSON.stringify(Math.round(assetObj.run1 / 3600)) + " h</p>");
          $("#E1").append("<p>" + JSON.stringify(Math.round(assetObj.run2 / 3600)) + " h</p>");
          $("#E4").append("<p>" + JSON.stringify(Math.round(assetObj.run4 / 3600)) + " h</p>");
          $("#Adresse").append("<ion-item><ion-icon></ion-icon><ion-note>" 
          +  assetObj.address.streetAddress 
          + ",\n" 
          +  assetObj.address.zipCode + " " 
          +  assetObj.address.city + "\n"
          +"</ion-note></ion-item>");
        });
      });
    });
  }*/
  
  ionViewDidLoad() {
    
    // Now we know the DOM is ready
    let options = {
      zone: document.getElementById('zone_joystick'),
      mode: 'static',
      position: {left: '50%', top: '50%'},
      color: 'blue',
      lockX: false,
      lockY: false,
      size: 200,
      catchDistance: 100,
      restJoystick: true,
      restOpacity: 100, 
    };
    let manager = nipplejs.create(options);
    manager.on('start move', function (evt, data) {
      console.log('Move started');
    }).on('end', function(evt, data) {
      executeRequest(14);
    }).on('dir:up', function(evt, data) {
      executeRequest(2);
    }).on('dir:down', function(evt, data) {
      executeRequest(7);
    }).on('dir:left plain:up', function(evt, data) {
      executeRequest(1);
    }).on('dir:left plain:down', function(evt, data) {
      executeRequest(6);
    }).on('dir:right plain:up', function(evt, data) {
      executeRequest(3);
    }).on('dir:right plain:down', function(evt, data) {
      executeRequest(8);
    });
}
  executeCmd(name, id:null, event){
    console.log("Name: " + name);
    if(event != null){
      console.log("ButtonId:" + id ); 
      executeRequest(name);
      this.keyPressed = true;
      this.currentKeyId = id;
    }
    else if(event == null && this.keyPressed && id == this.currentKeyId){
      console.log("ButtonId:" + id ); 
      executeRequest(name);
      this.keyPressed = false;
    }
  }
  executeCmdSTPBtn(name){
    executeRequest(name);
  }
}
