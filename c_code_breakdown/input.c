/* input_key_name @ 004036d0 */

/* maps key codes (DIK/virtual) to display labels */

char * __cdecl input_key_name(int key_code)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  
  if (key_code < 0x100) {
    iVar2 = GetKeyNameTextA(key_code << 0x10,(LPSTR)&input_key_name_buf,0x3f);
    if (iVar2 != 0) {
      return (char *)&input_key_name_buf;
    }
    switch(key_code) {
    case 1:
      return s_DIK_ESCAPE_004718d8;
    case 2:
      return s_DIK_1_004718d0;
    case 3:
      return s_DIK_2_004718c8;
    case 4:
      return s_DIK_3_004718c0;
    case 5:
      return s_DIK_4_004718b8;
    case 6:
      return s_DIK_5_004718b0;
    case 7:
      return s_DIK_6_004718a8;
    case 8:
      return s_DIK_7_004718a0;
    case 9:
      return s_DIK_8_00471898;
    case 10:
      return s_DIK_9_00471890;
    case 0xb:
      return s_DIK_0_00471888;
    case 0xc:
      return s_MINUS_00471880;
    case 0xd:
      return s_EQUALS_00471878;
    case 0xe:
      return &DAT_00471870;
    case 0xf:
      return &DAT_0047186c;
    case 0x10:
      return &DAT_00471868;
    case 0x11:
      return &DAT_00471864;
    case 0x12:
      return &DAT_00471860;
    case 0x13:
      return &DAT_0047185c;
    case 0x14:
      return &DAT_00471858;
    case 0x15:
      return &DAT_00471854;
    case 0x16:
      return &DAT_00471850;
    case 0x17:
      return &DAT_0047184c;
    case 0x18:
      return &DAT_00471848;
    case 0x19:
      return &DAT_00471844;
    case 0x1a:
      return s_LBRACKET_00471838;
    case 0x1b:
      return s_RBRACKET_0047182c;
    case 0x1c:
      return s_RETURN_00471824;
    case 0x1d:
      return s_LCONTROL_00471818;
    case 0x1e:
      return &DAT_00471814;
    case 0x1f:
      return &DAT_00471810;
    case 0x20:
      return &DAT_0047180c;
    case 0x21:
      return &DAT_00471808;
    case 0x22:
      return &DAT_00471804;
    case 0x23:
      return &DAT_00471800;
    case 0x24:
      return &DAT_004717fc;
    case 0x25:
      return &DAT_004717f8;
    case 0x26:
      return &DAT_004717f4;
    case 0x27:
      return s_SEMICOLON_004717e8;
    case 0x28:
      return s_APOSTROPHE_004717dc;
    case 0x29:
      return s_GRAVE_004717d4;
    case 0x2a:
      return s_LSHIFT_004717cc;
    case 0x2b:
      return s_BACKSLASH_004717c0;
    case 0x2c:
      return &DAT_004717bc;
    case 0x2d:
      return &DAT_004717b8;
    case 0x2e:
      return &DAT_004717b4;
    case 0x2f:
      return &DAT_004717b0;
    case 0x30:
      return &DAT_004717ac;
    case 0x31:
      return &DAT_004717a8;
    case 0x32:
      return &DAT_004717a4;
    case 0x33:
      return s_COMMA_0047179c;
    case 0x34:
      return s_PERIOD_00471794;
    case 0x35:
      return s_SLASH_0047178c;
    case 0x36:
      return s_RSHIFT_00471784;
    case 0x37:
      return s_MULTIPLY_00471778;
    case 0x38:
      return s_LMENU_00471770;
    case 0x39:
      return s_SPACE_00471768;
    case 0x3a:
      return s_CAPITAL_00471760;
    case 0x3b:
      return &DAT_0047175c;
    case 0x3c:
      return &DAT_00471758;
    case 0x3d:
      return &DAT_00471754;
    case 0x3e:
      return &DAT_00471750;
    case 0x3f:
      return &DAT_0047174c;
    case 0x40:
      return &DAT_00471748;
    case 0x41:
      return &DAT_00471744;
    case 0x42:
      return &DAT_00471740;
    case 0x43:
      return &DAT_0047173c;
    case 0x44:
      return &DAT_00471738;
    case 0x45:
      return s_NUMLOCK_00471730;
    case 0x46:
      return s_SCROLL_00471728;
    case 0x47:
      return s_NUMPAD7_00471720;
    case 0x48:
      return s_NUMPAD8_00471718;
    case 0x49:
      return s_NUMPAD9_00471710;
    case 0x4a:
      return s_SUBTRACT_00471704;
    case 0x4b:
      return s_NUMPAD4_004716fc;
    case 0x4c:
      return s_NUMPAD5_004716f4;
    case 0x4d:
      return s_NUMPAD6_004716ec;
    case 0x4e:
      return &DAT_004716e8;
    case 0x4f:
      return s_NUMPAD1_004716e0;
    case 0x50:
      return s_NUMPAD2_004716d8;
    case 0x51:
      return s_NUMPAD3_004716d0;
    case 0x52:
      return s_NUMPAD0_004716c8;
    case 0x53:
      return s_DECIMAL_004716c0;
    default:
      return s_unknown_label;
    case 0x56:
      return s_OEM_102_004716b8;
    case 0x57:
      return &DAT_004716b4;
    case 0x58:
      return &DAT_004716b0;
    case 100:
      return &DAT_004716ac;
    case 0x65:
      return &DAT_004716a8;
    case 0x66:
      return &DAT_004716a4;
    case 0x70:
      return &DAT_0047169c;
    case 0x73:
      return s_ABNT_C1_00471694;
    case 0x79:
      return s_CONVERT_0047168c;
    case 0x7b:
      return s_NOCONVERT_00471680;
    case 0x7d:
      return &DAT_0047167c;
    case 0x7e:
      return s_ABNT_C2_00471674;
    case 0x8d:
      return s_NUMPADEQUALS_00471664;
    case 0x90:
      return s_PREVTRACK_00471658;
    case 0x91:
      return &DAT_00471654;
    case 0x92:
      return s_COLON_0047164c;
    case 0x93:
      return s_UNDERLINE_00471640;
    case 0x94:
      return s_KANJI_00471638;
    case 0x95:
      return &DAT_00471630;
    case 0x96:
      return &DAT_0047162c;
    case 0x97:
      return s_UNLABELED_00471620;
    case 0x99:
      return s_NEXTTRACK_00471614;
    case 0x9c:
      return s_NUMPADENTER_00471608;
    case 0x9d:
      return s_RCONTROL_004715fc;
    case 0xa0:
      return &DAT_004715f4;
    case 0xa1:
      return s_CALCULATOR_004715e8;
    case 0xa2:
      return s_PLAYPAUSE_004715dc;
    case 0xa4:
      return s_MEDIASTOP_004715d0;
    case 0xae:
      return s_VOLUMEDOWN_004715c4;
    case 0xb0:
      return s_VOLUMEUP_004715b8;
    case 0xb2:
      return s_WEBHOME_004715b0;
    case 0xb3:
      return s_NUMPADCOMMA_004715a4;
    case 0xb5:
      return s_DIVIDE_0047159c;
    case 0xb7:
      return s_SYSRQ_00471594;
    case 0xb8:
      return s_RMENU_0047158c;
    case 0xc5:
      return s_PAUSE_00471584;
    case 199:
      return &DAT_0047157c;
    case 200:
      return &DAT_00471578;
    case 0xc9:
      return s_PRIOR_00471570;
    case 0xcb:
      return &DAT_00471568;
    case 0xcd:
      return s_RIGHT_00471560;
    case 0xcf:
      return &DAT_0047155c;
    case 0xd0:
      return &DAT_00471554;
    case 0xd1:
      return &DAT_0047154c;
    case 0xd2:
      return s_INSERT_00471544;
    case 0xd3:
      return s_DELETE_0047153c;
    case 0xdb:
      return &DAT_00471534;
    case 0xdc:
      return &DAT_0047152c;
    case 0xdd:
      return &DAT_00471524;
    case 0xde:
      return s_POWER_0047151c;
    case 0xdf:
      return s_SLEEP_00471514;
    case 0xe3:
      return &DAT_0047150c;
    case 0xe5:
      return s_WEBSEARCH_00471500;
    case 0xe6:
      return s_WEBFAVORITES_004714f0;
    case 0xe7:
      return s_WEBREFRESH_004714e4;
    case 0xe8:
      return s_WEBSTOP_004714dc;
    case 0xe9:
      return s_WEBFORWARD_004714d0;
    case 0xea:
      return s_WEBBACK_004714c8;
    case 0xeb:
      return s_MYCOMPUTER_004714bc;
    case 0xec:
      return &DAT_004714b4;
    case 0xed:
      return s_MEDIASELECT_004714a8;
    }
  }
  if (key_code == 0x100) {
    uVar3 = 0xffffffff;
    pcVar5 = s_Mouse1_00471af4;
    do {
      pcVar6 = pcVar5;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar6 = pcVar5 + 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar6;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar5 = pcVar6 + -uVar3;
    pcVar6 = (char *)&input_key_name_buf;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar6 = pcVar6 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar6 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar6 = pcVar6 + 1;
    }
    return (char *)&input_key_name_buf;
  }
  if (key_code == 0x101) {
    pcVar5 = s_Mouse2_00471aec;
  }
  else {
    if (key_code == 0x102) {
      uVar3 = 0xffffffff;
      pcVar5 = s_Mouse3_00471ae4;
      do {
        pcVar6 = pcVar5;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar6 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar6;
      } while (cVar1 != '\0');
      uVar3 = ~uVar3;
      pcVar5 = pcVar6 + -uVar3;
      pcVar6 = (char *)&input_key_name_buf;
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar6 = pcVar6 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar6 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar6 = pcVar6 + 1;
      }
      return (char *)&input_key_name_buf;
    }
    if (key_code == 0x103) {
      pcVar5 = s_Mouse4_00471adc;
    }
    else {
      if (key_code == 0x104) {
        uVar3 = 0xffffffff;
        pcVar5 = &DAT_00471ad4;
        do {
          pcVar6 = pcVar5;
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          pcVar6 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar6;
        } while (cVar1 != '\0');
        uVar3 = ~uVar3;
        pcVar5 = pcVar6 + -uVar3;
        pcVar6 = (char *)&input_key_name_buf;
        for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
          *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          pcVar6 = pcVar6 + 4;
        }
        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *pcVar6 = *pcVar5;
          pcVar5 = pcVar5 + 1;
          pcVar6 = pcVar6 + 1;
        }
        return (char *)&input_key_name_buf;
      }
      if (key_code == 0x109) {
        pcVar5 = s_MWheelUp_00471ac8;
      }
      else {
        if (key_code == 0x10a) {
          uVar3 = 0xffffffff;
          pcVar5 = s_MWheelDown_00471abc;
          do {
            pcVar6 = pcVar5;
            if (uVar3 == 0) break;
            uVar3 = uVar3 - 1;
            pcVar6 = pcVar5 + 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar6;
          } while (cVar1 != '\0');
          uVar3 = ~uVar3;
          pcVar5 = pcVar6 + -uVar3;
          pcVar6 = (char *)&input_key_name_buf;
          for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
            *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
            pcVar5 = pcVar5 + 4;
            pcVar6 = pcVar6 + 4;
          }
          for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
            *pcVar6 = *pcVar5;
            pcVar5 = pcVar5 + 1;
            pcVar6 = pcVar6 + 1;
          }
          return (char *)&input_key_name_buf;
        }
        if (key_code == 0x11f) {
          pcVar5 = s_Joys1_00471ab4;
        }
        else {
          if (key_code == 0x120) {
            uVar3 = 0xffffffff;
            pcVar5 = &DAT_00471aac;
            do {
              pcVar6 = pcVar5;
              if (uVar3 == 0) break;
              uVar3 = uVar3 - 1;
              pcVar6 = pcVar5 + 1;
              cVar1 = *pcVar5;
              pcVar5 = pcVar6;
            } while (cVar1 != '\0');
            uVar3 = ~uVar3;
            pcVar5 = pcVar6 + -uVar3;
            pcVar6 = (char *)&input_key_name_buf;
            for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
              *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
              pcVar5 = pcVar5 + 4;
              pcVar6 = pcVar6 + 4;
            }
            for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
              *pcVar6 = *pcVar5;
              pcVar5 = pcVar5 + 1;
              pcVar6 = pcVar6 + 1;
            }
            return (char *)&input_key_name_buf;
          }
          if (key_code == 0x121) {
            pcVar5 = s_Joys3_00471aa4;
          }
          else {
            if (key_code == 0x122) {
              uVar3 = 0xffffffff;
              pcVar5 = &DAT_00471a9c;
              do {
                pcVar6 = pcVar5;
                if (uVar3 == 0) break;
                uVar3 = uVar3 - 1;
                pcVar6 = pcVar5 + 1;
                cVar1 = *pcVar5;
                pcVar5 = pcVar6;
              } while (cVar1 != '\0');
              uVar3 = ~uVar3;
              pcVar5 = pcVar6 + -uVar3;
              pcVar6 = (char *)&input_key_name_buf;
              for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
                *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
                pcVar5 = pcVar5 + 4;
                pcVar6 = pcVar6 + 4;
              }
              for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
                *pcVar6 = *pcVar5;
                pcVar5 = pcVar5 + 1;
                pcVar6 = pcVar6 + 1;
              }
              return (char *)&input_key_name_buf;
            }
            if (key_code == 0x123) {
              pcVar5 = s_Joys5_00471a94;
            }
            else {
              if (key_code == 0x124) {
                uVar3 = 0xffffffff;
                pcVar5 = &DAT_00471a8c;
                do {
                  pcVar6 = pcVar5;
                  if (uVar3 == 0) break;
                  uVar3 = uVar3 - 1;
                  pcVar6 = pcVar5 + 1;
                  cVar1 = *pcVar5;
                  pcVar5 = pcVar6;
                } while (cVar1 != '\0');
                uVar3 = ~uVar3;
                pcVar5 = pcVar6 + -uVar3;
                pcVar6 = (char *)&input_key_name_buf;
                for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
                  *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
                  pcVar5 = pcVar5 + 4;
                  pcVar6 = pcVar6 + 4;
                }
                for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
                  *pcVar6 = *pcVar5;
                  pcVar5 = pcVar5 + 1;
                  pcVar6 = pcVar6 + 1;
                }
                return (char *)&input_key_name_buf;
              }
              if (key_code == 0x125) {
                pcVar5 = s_Joys7_00471a84;
              }
              else {
                if (key_code == 0x126) {
                  uVar3 = 0xffffffff;
                  pcVar5 = &DAT_00471a7c;
                  do {
                    pcVar6 = pcVar5;
                    if (uVar3 == 0) break;
                    uVar3 = uVar3 - 1;
                    pcVar6 = pcVar5 + 1;
                    cVar1 = *pcVar5;
                    pcVar5 = pcVar6;
                  } while (cVar1 != '\0');
                  uVar3 = ~uVar3;
                  pcVar5 = pcVar6 + -uVar3;
                  pcVar6 = (char *)&input_key_name_buf;
                  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
                    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
                    pcVar5 = pcVar5 + 4;
                    pcVar6 = pcVar6 + 4;
                  }
                  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
                    *pcVar6 = *pcVar5;
                    pcVar5 = pcVar5 + 1;
                    pcVar6 = pcVar6 + 1;
                  }
                  return (char *)&input_key_name_buf;
                }
                if (key_code == 0x127) {
                  pcVar5 = s_Joys9_00471a74;
                }
                else {
                  if (key_code == 0x128) {
                    uVar3 = 0xffffffff;
                    pcVar5 = &DAT_00471a6c;
                    do {
                      pcVar6 = pcVar5;
                      if (uVar3 == 0) break;
                      uVar3 = uVar3 - 1;
                      pcVar6 = pcVar5 + 1;
                      cVar1 = *pcVar5;
                      pcVar5 = pcVar6;
                    } while (cVar1 != '\0');
                    uVar3 = ~uVar3;
                    pcVar5 = pcVar6 + -uVar3;
                    pcVar6 = (char *)&input_key_name_buf;
                    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
                      *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
                      pcVar5 = pcVar5 + 4;
                      pcVar6 = pcVar6 + 4;
                    }
                    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
                      *pcVar6 = *pcVar5;
                      pcVar5 = pcVar5 + 1;
                      pcVar6 = pcVar6 + 1;
                    }
                    return (char *)&input_key_name_buf;
                  }
                  if (key_code == 0x129) {
                    pcVar5 = s_Joys11;
                  }
                  else {
                    if (key_code == 0x12a) {
                      uVar3 = 0xffffffff;
                      pcVar5 = &s_Joys12;
                      do {
                        pcVar6 = pcVar5;
                        if (uVar3 == 0) break;
                        uVar3 = uVar3 - 1;
                        pcVar6 = pcVar5 + 1;
                        cVar1 = *pcVar5;
                        pcVar5 = pcVar6;
                      } while (cVar1 != '\0');
                      uVar3 = ~uVar3;
                      pcVar5 = pcVar6 + -uVar3;
                      pcVar6 = (char *)&input_key_name_buf;
                      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
                        *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
                        pcVar5 = pcVar5 + 4;
                        pcVar6 = pcVar6 + 4;
                      }
                      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
                        *pcVar6 = *pcVar5;
                        pcVar5 = pcVar5 + 1;
                        pcVar6 = pcVar6 + 1;
                      }
                      return (char *)&input_key_name_buf;
                    }
                    if (key_code == 0x131) {
                      pcVar5 = s_JoysUp;
                    }
                    else {
                      if (key_code == 0x132) {
                        uVar3 = 0xffffffff;
                        pcVar5 = s_JoysDown;
                        do {
                          pcVar6 = pcVar5;
                          if (uVar3 == 0) break;
                          uVar3 = uVar3 - 1;
                          pcVar6 = pcVar5 + 1;
                          cVar1 = *pcVar5;
                          pcVar5 = pcVar6;
                        } while (cVar1 != '\0');
                        uVar3 = ~uVar3;
                        pcVar5 = pcVar6 + -uVar3;
                        pcVar6 = (char *)&input_key_name_buf;
                        for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
                          *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
                          pcVar5 = pcVar5 + 4;
                          pcVar6 = pcVar6 + 4;
                        }
                        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
                          *pcVar6 = *pcVar5;
                          pcVar5 = pcVar5 + 1;
                          pcVar6 = pcVar6 + 1;
                        }
                        return (char *)&input_key_name_buf;
                      }
                      if (key_code == 0x133) {
                        pcVar5 = s_JoysLeft;
                      }
                      else {
                        if (key_code == 0x134) {
                          uVar3 = 0xffffffff;
                          pcVar5 = s_JoysRight;
                          do {
                            pcVar6 = pcVar5;
                            if (uVar3 == 0) break;
                            uVar3 = uVar3 - 1;
                            pcVar6 = pcVar5 + 1;
                            cVar1 = *pcVar5;
                            pcVar5 = pcVar6;
                          } while (cVar1 != '\0');
                          uVar3 = ~uVar3;
                          pcVar5 = pcVar6 + -uVar3;
                          pcVar6 = (char *)&input_key_name_buf;
                          for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
                            *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
                            pcVar5 = pcVar5 + 4;
                            pcVar6 = pcVar6 + 4;
                          }
                          for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
                            *pcVar6 = *pcVar5;
                            pcVar5 = pcVar5 + 1;
                            pcVar6 = pcVar6 + 1;
                          }
                          return (char *)&input_key_name_buf;
                        }
                        if (key_code == 0x13f) {
                          pcVar5 = s_JoyAxisX;
                        }
                        else {
                          if (key_code == 0x140) {
                            uVar3 = 0xffffffff;
                            pcVar5 = s_JoyAxisY;
                            do {
                              pcVar6 = pcVar5;
                              if (uVar3 == 0) break;
                              uVar3 = uVar3 - 1;
                              pcVar6 = pcVar5 + 1;
                              cVar1 = *pcVar5;
                              pcVar5 = pcVar6;
                            } while (cVar1 != '\0');
                            uVar3 = ~uVar3;
                            pcVar5 = pcVar6 + -uVar3;
                            pcVar6 = (char *)&input_key_name_buf;
                            for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
                              *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
                              pcVar5 = pcVar5 + 4;
                              pcVar6 = pcVar6 + 4;
                            }
                            for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
                              *pcVar6 = *pcVar5;
                              pcVar5 = pcVar5 + 1;
                              pcVar6 = pcVar6 + 1;
                            }
                            return (char *)&input_key_name_buf;
                          }
                          if (key_code == 0x141) {
                            pcVar5 = s_JoyAxisZ;
                          }
                          else {
                            if (key_code == 0x153) {
                              uVar3 = 0xffffffff;
                              pcVar5 = &s_RIM0XAxis;
                              do {
                                pcVar6 = pcVar5;
                                if (uVar3 == 0) break;
                                uVar3 = uVar3 - 1;
                                pcVar6 = pcVar5 + 1;
                                cVar1 = *pcVar5;
                                pcVar5 = pcVar6;
                              } while (cVar1 != '\0');
                              uVar3 = ~uVar3;
                              pcVar5 = pcVar6 + -uVar3;
                              pcVar6 = (char *)&input_key_name_buf;
                              for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
                                *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
                                pcVar5 = pcVar5 + 4;
                                pcVar6 = pcVar6 + 4;
                              }
                              for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
                                *pcVar6 = *pcVar5;
                                pcVar5 = pcVar5 + 1;
                                pcVar6 = pcVar6 + 1;
                              }
                              return (char *)&input_key_name_buf;
                            }
                            if (key_code == 0x154) {
                              pcVar5 = s_JoyRotY_004719fc;
                            }
                            else {
                              if (key_code == 0x155) {
                                uVar3 = 0xffffffff;
                                pcVar5 = &DAT_004719f4;
                                do {
                                  pcVar6 = pcVar5;
                                  if (uVar3 == 0) break;
                                  uVar3 = uVar3 - 1;
                                  pcVar6 = pcVar5 + 1;
                                  cVar1 = *pcVar5;
                                  pcVar5 = pcVar6;
                                } while (cVar1 != '\0');
                                uVar3 = ~uVar3;
                                pcVar5 = pcVar6 + -uVar3;
                                pcVar6 = (char *)&input_key_name_buf;
                                for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
                                  *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
                                  pcVar5 = pcVar5 + 4;
                                  pcVar6 = pcVar6 + 4;
                                }
                                for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
                                  *pcVar6 = *pcVar5;
                                  pcVar5 = pcVar5 + 1;
                                  pcVar6 = pcVar6 + 1;
                                }
                                return (char *)&input_key_name_buf;
                              }
                              if (key_code == 0x17e) {
                                pcVar5 = s_unbound_004719ec;
                              }
                              else {
                                if (key_code == 0x163) {
                                  uVar3 = 0xffffffff;
                                  pcVar5 = &DAT_004719e0;
                                  do {
                                    pcVar6 = pcVar5;
                                    if (uVar3 == 0) break;
                                    uVar3 = uVar3 - 1;
                                    pcVar6 = pcVar5 + 1;
                                    cVar1 = *pcVar5;
                                    pcVar5 = pcVar6;
                                  } while (cVar1 != '\0');
                                  uVar3 = ~uVar3;
                                  pcVar5 = pcVar6 + -uVar3;
                                  pcVar6 = (char *)&input_key_name_buf;
                                  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
                                    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
                                    pcVar5 = pcVar5 + 4;
                                    pcVar6 = pcVar6 + 4;
                                  }
                                  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
                                    *pcVar6 = *pcVar5;
                                    pcVar5 = pcVar5 + 1;
                                    pcVar6 = pcVar6 + 1;
                                  }
                                  return (char *)&input_key_name_buf;
                                }
                                if (key_code == 0x164) {
                                  pcVar5 = s_RIM1XAxis_004719d4;
                                }
                                else {
                                  if (key_code == 0x165) {
                                    uVar3 = 0xffffffff;
                                    pcVar5 = &DAT_004719c8;
                                    do {
                                      pcVar6 = pcVar5;
                                      if (uVar3 == 0) break;
                                      uVar3 = uVar3 - 1;
                                      pcVar6 = pcVar5 + 1;
                                      cVar1 = *pcVar5;
                                      pcVar5 = pcVar6;
                                    } while (cVar1 != '\0');
                                    uVar3 = ~uVar3;
                                    pcVar5 = pcVar6 + -uVar3;
                                    pcVar6 = (char *)&input_key_name_buf;
                                    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
                                      *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
                                      pcVar5 = pcVar5 + 4;
                                      pcVar6 = pcVar6 + 4;
                                    }
                                    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
                                      *pcVar6 = *pcVar5;
                                      pcVar5 = pcVar5 + 1;
                                      pcVar6 = pcVar6 + 1;
                                    }
                                    return (char *)&input_key_name_buf;
                                  }
                                  if (key_code == 0x168) {
                                    pcVar5 = s_RIM0YAxis_004719bc;
                                  }
                                  else {
                                    if (key_code == 0x169) {
                                      uVar3 = 0xffffffff;
                                      pcVar5 = &DAT_004719b0;
                                      do {
                                        pcVar6 = pcVar5;
                                        if (uVar3 == 0) break;
                                        uVar3 = uVar3 - 1;
                                        pcVar6 = pcVar5 + 1;
                                        cVar1 = *pcVar5;
                                        pcVar5 = pcVar6;
                                      } while (cVar1 != '\0');
                                      uVar3 = ~uVar3;
                                      pcVar5 = pcVar6 + -uVar3;
                                      pcVar6 = (char *)&input_key_name_buf;
                                      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
                                        *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
                                        pcVar5 = pcVar5 + 4;
                                        pcVar6 = pcVar6 + 4;
                                      }
                                      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
                                        *pcVar6 = *pcVar5;
                                        pcVar5 = pcVar5 + 1;
                                        pcVar6 = pcVar6 + 1;
                                      }
                                      return (char *)&input_key_name_buf;
                                    }
                                    if (key_code == 0x16a) {
                                      pcVar5 = s_RIM2YAxis_004719a4;
                                    }
                                    else {
                                      if (key_code == 0x16d) {
                                        uVar3 = 0xffffffff;
                                        pcVar5 = &DAT_00471998;
                                        do {
                                          pcVar6 = pcVar5;
                                          if (uVar3 == 0) break;
                                          uVar3 = uVar3 - 1;
                                          pcVar6 = pcVar5 + 1;
                                          cVar1 = *pcVar5;
                                          pcVar5 = pcVar6;
                                        } while (cVar1 != '\0');
                                        uVar3 = ~uVar3;
                                        pcVar5 = pcVar6 + -uVar3;
                                        pcVar6 = (char *)&input_key_name_buf;
                                        for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
                                          *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
                                          pcVar5 = pcVar5 + 4;
                                          pcVar6 = pcVar6 + 4;
                                        }
                                        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
                                          *pcVar6 = *pcVar5;
                                          pcVar5 = pcVar5 + 1;
                                          pcVar6 = pcVar6 + 1;
                                        }
                                        return (char *)&input_key_name_buf;
                                      }
                                      if (key_code == 0x16e) {
                                        pcVar5 = s_RIM0Btn2_0047198c;
                                      }
                                      else {
                                        if (key_code == 0x16f) {
                                          uVar3 = 0xffffffff;
                                          pcVar5 = &DAT_00471980;
                                          do {
                                            pcVar6 = pcVar5;
                                            if (uVar3 == 0) break;
                                            uVar3 = uVar3 - 1;
                                            pcVar6 = pcVar5 + 1;
                                            cVar1 = *pcVar5;
                                            pcVar5 = pcVar6;
                                          } while (cVar1 != '\0');
                                          uVar3 = ~uVar3;
                                          pcVar5 = pcVar6 + -uVar3;
                                          pcVar6 = (char *)&input_key_name_buf;
                                          for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
                                            *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
                                            pcVar5 = pcVar5 + 4;
                                            pcVar6 = pcVar6 + 4;
                                          }
                                          for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
                                            *pcVar6 = *pcVar5;
                                            pcVar5 = pcVar5 + 1;
                                            pcVar6 = pcVar6 + 1;
                                          }
                                          return (char *)&input_key_name_buf;
                                        }
                                        if (key_code == 0x170) {
                                          pcVar5 = s_RIM0Btn4_00471974;
                                        }
                                        else {
                                          if (key_code == 0x171) {
                                            uVar3 = 0xffffffff;
                                            pcVar5 = &DAT_00471968;
                                            do {
                                              pcVar6 = pcVar5;
                                              if (uVar3 == 0) break;
                                              uVar3 = uVar3 - 1;
                                              pcVar6 = pcVar5 + 1;
                                              cVar1 = *pcVar5;
                                              pcVar5 = pcVar6;
                                            } while (cVar1 != '\0');
                                            uVar3 = ~uVar3;
                                            pcVar5 = pcVar6 + -uVar3;
                                            pcVar6 = (char *)&input_key_name_buf;
                                            for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1)
                                            {
                                              *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
                                              pcVar5 = pcVar5 + 4;
                                              pcVar6 = pcVar6 + 4;
                                            }
                                            for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
                                              *pcVar6 = *pcVar5;
                                              pcVar5 = pcVar5 + 1;
                                              pcVar6 = pcVar6 + 1;
                                            }
                                            return (char *)&input_key_name_buf;
                                          }
                                          if (key_code == 0x172) {
                                            pcVar5 = s_RIM1Btn1_0047195c;
                                          }
                                          else {
                                            if (key_code == 0x173) {
                                              uVar3 = 0xffffffff;
                                              pcVar5 = &DAT_00471950;
                                              do {
                                                pcVar6 = pcVar5;
                                                if (uVar3 == 0) break;
                                                uVar3 = uVar3 - 1;
                                                pcVar6 = pcVar5 + 1;
                                                cVar1 = *pcVar5;
                                                pcVar5 = pcVar6;
                                              } while (cVar1 != '\0');
                                              uVar3 = ~uVar3;
                                              pcVar5 = pcVar6 + -uVar3;
                                              pcVar6 = (char *)&input_key_name_buf;
                                              for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1
                                                  ) {
                                                *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
                                                pcVar5 = pcVar5 + 4;
                                                pcVar6 = pcVar6 + 4;
                                              }
                                              for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1)
                                              {
                                                *pcVar6 = *pcVar5;
                                                pcVar5 = pcVar5 + 1;
                                                pcVar6 = pcVar6 + 1;
                                              }
                                              return (char *)&input_key_name_buf;
                                            }
                                            if (key_code == 0x174) {
                                              pcVar5 = s_RIM1Btn3_00471944;
                                            }
                                            else {
                                              if (key_code == 0x175) {
                                                uVar3 = 0xffffffff;
                                                pcVar5 = &DAT_00471938;
                                                do {
                                                  pcVar6 = pcVar5;
                                                  if (uVar3 == 0) break;
                                                  uVar3 = uVar3 - 1;
                                                  pcVar6 = pcVar5 + 1;
                                                  cVar1 = *pcVar5;
                                                  pcVar5 = pcVar6;
                                                } while (cVar1 != '\0');
                                                uVar3 = ~uVar3;
                                                pcVar5 = pcVar6 + -uVar3;
                                                pcVar6 = (char *)&input_key_name_buf;
                                                for (uVar4 = uVar3 >> 2; uVar4 != 0;
                                                    uVar4 = uVar4 - 1) {
                                                  *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
                                                  pcVar5 = pcVar5 + 4;
                                                  pcVar6 = pcVar6 + 4;
                                                }
                                                for (uVar3 = uVar3 & 3; uVar3 != 0;
                                                    uVar3 = uVar3 - 1) {
                                                  *pcVar6 = *pcVar5;
                                                  pcVar5 = pcVar5 + 1;
                                                  pcVar6 = pcVar6 + 1;
                                                }
                                                return (char *)&input_key_name_buf;
                                              }
                                              if (key_code == 0x176) {
                                                pcVar5 = s_RIM1Btn5_0047192c;
                                              }
                                              else {
                                                if (key_code == 0x177) {
                                                  uVar3 = 0xffffffff;
                                                  pcVar5 = &DAT_00471920;
                                                  do {
                                                    pcVar6 = pcVar5;
                                                    if (uVar3 == 0) break;
                                                    uVar3 = uVar3 - 1;
                                                    pcVar6 = pcVar5 + 1;
                                                    cVar1 = *pcVar5;
                                                    pcVar5 = pcVar6;
                                                  } while (cVar1 != '\0');
                                                  uVar3 = ~uVar3;
                                                  pcVar5 = pcVar6 + -uVar3;
                                                  pcVar6 = (char *)&input_key_name_buf;
                                                  for (uVar4 = uVar3 >> 2; uVar4 != 0;
                                                      uVar4 = uVar4 - 1) {
                                                    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
                                                    pcVar5 = pcVar5 + 4;
                                                    pcVar6 = pcVar6 + 4;
                                                  }
                                                  for (uVar3 = uVar3 & 3; uVar3 != 0;
                                                      uVar3 = uVar3 - 1) {
                                                    *pcVar6 = *pcVar5;
                                                    pcVar5 = pcVar5 + 1;
                                                    pcVar6 = pcVar6 + 1;
                                                  }
                                                  return (char *)&input_key_name_buf;
                                                }
                                                if (key_code == 0x178) {
                                                  pcVar5 = s_RIM2Btn2_00471914;
                                                }
                                                else {
                                                  if (key_code == 0x179) {
                                                    uVar3 = 0xffffffff;
                                                    pcVar5 = &DAT_00471908;
                                                    do {
                                                      pcVar6 = pcVar5;
                                                      if (uVar3 == 0) break;
                                                      uVar3 = uVar3 - 1;
                                                      pcVar6 = pcVar5 + 1;
                                                      cVar1 = *pcVar5;
                                                      pcVar5 = pcVar6;
                                                    } while (cVar1 != '\0');
                                                    uVar3 = ~uVar3;
                                                    pcVar5 = pcVar6 + -uVar3;
                                                    pcVar6 = (char *)&input_key_name_buf;
                                                    for (uVar4 = uVar3 >> 2; uVar4 != 0;
                                                        uVar4 = uVar4 - 1) {
                                                      *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
                                                      pcVar5 = pcVar5 + 4;
                                                      pcVar6 = pcVar6 + 4;
                                                    }
                                                    for (uVar3 = uVar3 & 3; uVar3 != 0;
                                                        uVar3 = uVar3 - 1) {
                                                      *pcVar6 = *pcVar5;
                                                      pcVar5 = pcVar5 + 1;
                                                      pcVar6 = pcVar6 + 1;
                                                    }
                                                    return (char *)&input_key_name_buf;
                                                  }
                                                  if (key_code == 0x17a) {
                                                    pcVar5 = s_RIM2Btn4_004718fc;
                                                  }
                                                  else {
                                                    if (key_code == 0x17b) {
                                                      uVar3 = 0xffffffff;
                                                      pcVar5 = &DAT_004718f0;
                                                      do {
                                                        pcVar6 = pcVar5;
                                                        if (uVar3 == 0) break;
                                                        uVar3 = uVar3 - 1;
                                                        pcVar6 = pcVar5 + 1;
                                                        cVar1 = *pcVar5;
                                                        pcVar5 = pcVar6;
                                                      } while (cVar1 != '\0');
                                                      uVar3 = ~uVar3;
                                                      pcVar5 = pcVar6 + -uVar3;
                                                      pcVar6 = (char *)&input_key_name_buf;
                                                      for (uVar4 = uVar3 >> 2; uVar4 != 0;
                                                          uVar4 = uVar4 - 1) {
                                                        *(undefined4 *)pcVar6 =
                                                             *(undefined4 *)pcVar5;
                                                        pcVar5 = pcVar5 + 4;
                                                        pcVar6 = pcVar6 + 4;
                                                      }
                                                      for (uVar3 = uVar3 & 3; uVar3 != 0;
                                                          uVar3 = uVar3 - 1) {
                                                        *pcVar6 = *pcVar5;
                                                        pcVar5 = pcVar5 + 1;
                                                        pcVar6 = pcVar6 + 1;
                                                      }
                                                      return (char *)&input_key_name_buf;
                                                    }
                                                    if (key_code < 0x164) goto LAB_00403e30;
                                                    pcVar5 = s_RawInput___004718e4;
                                                  }
                                                }
                                              }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  uVar3 = 0xffffffff;
  do {
    pcVar6 = pcVar5;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar6 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar6;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar5 = pcVar6 + -uVar3;
  pcVar6 = (char *)&input_key_name_buf;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar6 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
  }
LAB_00403e30:
  return (char *)&input_key_name_buf;
}



/* joystick_pov_check_up @ 0041e8d0 */

bool joystick_pov_check_up(void)

{
  int iVar1;
  
  iVar1 = (*grim_interface_ptr->vtable->grim_get_joystick_pov)(0);
  return iVar1 == config_blob.reserved1._16_4_;
}



/* joystick_pov_check_down @ 0041e8f0 */

bool joystick_pov_check_down(void)

{
  int iVar1;
  
  iVar1 = (*grim_interface_ptr->vtable->grim_get_joystick_pov)(0);
  return iVar1 == config_blob.reserved1._12_4_;
}



/* input_any_key_pressed @ 00446000 */

/* returns true if any key is down (scans keycodes 2..0x17e) */

int input_any_key_pressed(void)

{
  int iVar1;
  int key;
  
  key = 2;
  do {
    iVar1 = (*grim_interface_ptr->vtable->grim_is_key_active)(key);
    if ((char)iVar1 != '\0') {
      return CONCAT31((int3)((uint)iVar1 >> 8),1);
    }
    key = key + 1;
  } while (key < 0x17f);
  return iVar1;
}



/* input_primary_just_pressed @ 00446030 */

/* edge-detect primary action (mouse button 0 or per-player fire key DAT_00490bec) */

int input_primary_just_pressed(void)

{
  undefined4 in_EAX;
  uint3 uVar2;
  int iVar1;
  uint3 extraout_var;
  int *piVar3;
  bool bVar4;
  
  uVar2 = (uint3)((uint)in_EAX >> 8);
  if (console_open_flag == '\0') {
    if (input_primary_latch == '\0') {
      iVar1 = (*grim_interface_ptr->vtable->grim_is_mouse_button_down)(0);
      if ((char)iVar1 != '\0') {
        input_primary_latch = '\x01';
      }
      piVar3 = &player_state_table.input.fire_key;
      do {
        iVar1 = (*grim_interface_ptr->vtable->grim_is_key_active)(*piVar3);
        if ((char)iVar1 != '\0') {
          input_primary_latch = '\x01';
        }
        piVar3 = piVar3 + 0xd8;
      } while ((int)piVar3 < 0x4912ac);
      uVar2 = (uint3)((uint)iVar1 >> 8);
      if (input_primary_latch != '\0') {
        return CONCAT31(uVar2,1);
      }
    }
    else {
      iVar1 = (*grim_interface_ptr->vtable->grim_is_mouse_button_down)(0);
      bVar4 = (char)iVar1 == '\0';
      piVar3 = &player_state_table.input.fire_key;
      do {
        iVar1 = (*grim_interface_ptr->vtable->grim_is_key_active)(*piVar3);
        extraout_var = (uint3)((uint)iVar1 >> 8);
        if ((char)iVar1 != '\0') {
          bVar4 = false;
        }
        piVar3 = piVar3 + 0xd8;
      } while ((int)piVar3 < 0x4912ac);
      uVar2 = extraout_var;
      if (bVar4) {
        input_primary_latch = '\0';
      }
    }
  }
  return (uint)uVar2 << 8;
}



/* input_primary_is_down @ 004460f0 */

/* returns true while primary action is held (mouse button 0 or primary fire keys) */

int input_primary_is_down(void)

{
  int iVar1;
  
  iVar1 = (*grim_interface_ptr->vtable->grim_is_mouse_button_down)(0);
  if ((char)iVar1 == '\0') {
    iVar1 = (*grim_interface_ptr->vtable->grim_is_key_active)(player_state_table.input.fire_key);
    if ((char)iVar1 == '\0') {
      iVar1 = (*grim_interface_ptr->vtable->grim_is_key_active)(player_alt_fire_key);
      if ((char)iVar1 == '\0') {
        return 0;
      }
    }
  }
  return 1;
}



/* input_scheme_label @ 00447cf0 */

/* maps control scheme ids to labels (Relative/Static/Dual Action Pad/etc) */

char * __cdecl input_scheme_label(int scheme)

{
  switch(scheme) {
  case 1:
    return s_input_scheme_relative;
  case 2:
    return s_input_scheme_static;
  case 3:
    return s_input_scheme_dual_action;
  case 4:
    return s_input_scheme_mouse_click;
  case 5:
    return s_input_scheme_computer;
  default:
    return s_unknown_label;
  }
}



/* input_get_active_axis @ 00448b50 */

undefined4 __fastcall input_get_active_axis(undefined4 param_1)

{
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float10 extraout_ST0_02;
  float10 extraout_ST0_03;
  float10 extraout_ST0_04;
  
  (*grim_interface_ptr->vtable->grim_get_config_float)(0x13f);
  if (0.5 < ABS((float)extraout_ST0)) {
    return 0x13f;
  }
  (*grim_interface_ptr->vtable->grim_get_config_float)(0x140);
  if (0.5 < ABS((float)extraout_ST0_00)) {
    return 0x140;
  }
  (*grim_interface_ptr->vtable->grim_get_config_float)(0x141);
  if (0.5 < ABS((float)extraout_ST0_01)) {
    return 0x141;
  }
  (*grim_interface_ptr->vtable->grim_get_config_float)(0x153);
  if (0.5 < ABS((float)extraout_ST0_02)) {
    return 0x153;
  }
  (*grim_interface_ptr->vtable->grim_get_config_float)(0x154);
  if (0.5 < ABS((float)extraout_ST0_03)) {
    return 0x154;
  }
  (*grim_interface_ptr->vtable->grim_get_config_float)(0x155);
  if (0.5 < ABS((float)extraout_ST0_04)) {
    return 0x155;
  }
  (*grim_interface_ptr->vtable->grim_flush_input)();
  return 0;
}


