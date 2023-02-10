/*
 * @Author: rx-ted
 * @Date: 2023-01-20 19:52:12
 * @LastEditors: rx-ted
 * @LastEditTime: 2023-01-22 17:11:11
 */
/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file main.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g4fr.h"
#include"rtconfig.h"

#ifdef PINTONUM
void pinToNum(void)
{
    char *ch = "num - PORTx-PIN\n0<--->A0    \n1<--->A1    \n2<--->A2    \n3<--->A3    \n4<--->A4    \n5<--->A5    \n6<--->A6    \n7<--->A7    \n8<--->A8    \n9<--->A9    \n10<--->A10   \n11<--->A11   \n12<--->A12   \n13<--->A13   \n14<--->A14   \n15<--->A15   \n16<--->B0   \n17<--->B1   \n18<--->B2   \n19<--->B3   \n20<--->B4   \n21<--->B5   \n22<--->B6   \n23<--->B7   \n24<--->B8   \n25<--->B9   \n26<--->B10   \n27<--->B11   \n28<--->B12   \n29<--->B13   \n30<--->B14   \n31<--->B15   \n32<--->C0   \n33<--->C1   \n34<--->C2   \n35<--->C3   \n36<--->C4   \n37<--->C5   \n38<--->C6   \n39<--->C7   \n40<--->C8   \n41<--->C9   \n42<--->C10   \n43<--->C11   \n44<--->C12   \n45<--->C13   \n46<--->C14   \n47<--->C15   \n48<--->D0   \n49<--->D1   \n50<--->D2   \n51<--->D3   \n52<--->D4   \n53<--->D5   \n54<--->D6   \n55<--->D7   \n56<--->D8   \n57<--->D9   \n58<--->D10   \n59<--->D11   \n60<--->D12   \n61<--->D13   \n62<--->D14   \n63<--->D15   \n64<--->E0   \n65<--->E1   \n66<--->E2   \n67<--->E3   \n68<--->E4   \n69<--->E5   \n70<--->E6   \n71<--->E7   \n72<--->E8   \n73<--->E9   \n74<--->E10   \n75<--->E11   \n76<--->E12   \n77<--->E13   \n78<--->E14\n79<--->E15\n";
    rt_kprintf("%s", ch);
}
MSH_CMD_EXPORT(pinToNum, "pin number to protx-pin")

#endif // PINTONUM


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
