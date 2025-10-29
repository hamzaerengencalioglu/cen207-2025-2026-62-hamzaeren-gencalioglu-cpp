﻿#ifndef USER_AUTHENTICATION_H
#define USER_AUTHENTICATION_H

#include "../../utility/header/file_utility.h"          // HashTable, User, dosya işlemleri
#include "../../local_event_planner/header/wait.h"      // WAIT makrosu (buradan geliyor)
#include "menu.h"                                       // Menü çağrıları için


// Test sırasında mainMenu'yu devre dışı bırakmak için global bayrak
extern bool isTestEnvironment;

// Kullanıcı giriş ve kayıt işlemleri
int performUserLogin(HashTable* ht);
int performUserRegistration(HashTable* ht);

// Dosya yükleme ve kaydetme ile çalışan yüksek seviye işlemler
int initiateUserRegistration();
int initiateUserLogin();


#endif // USER_AUTHENTICATION_H
