import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { RouteReuseStrategy } from '@angular/router';

import { IonicModule, IonicRouteStrategy } from '@ionic/angular';

import { AppComponent } from './app.component';
import { AppRoutingModule } from './app-routing.module';
import { initializeApp, provideFirebaseApp } from '@angular/fire/app';
import { getFirestore, provideFirestore } from '@angular/fire/firestore';
import { environment } from 'src/environments/environment';


@NgModule({
  declarations: [AppComponent],
  imports: [BrowserModule, IonicModule.forRoot(), AppRoutingModule, provideFirebaseApp(() => initializeApp(environment.firebase)),
    provideFirestore(() => getFirestore()),
    provideFirebaseApp(() => initializeApp({"projectId":"iote3-9954c","appId":"1:171360217797:web:16b78f618a81248bf01eac","storageBucket":"iote3-9954c.appspot.com","apiKey":"AIzaSyCPrDAh2PF5-kyfCihPyZGTxljDaF5dsHg","authDomain":"iote3-9954c.firebaseapp.com","messagingSenderId":"171360217797","measurementId":"G-04CE5WDEND"}))],
  providers: [{ provide: RouteReuseStrategy, useClass: IonicRouteStrategy }],
  bootstrap: [AppComponent],
})
export class AppModule {}
