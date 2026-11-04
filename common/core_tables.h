/*****************************************************************************
 * Free42 -- an HP-42S calculator simulator
 * Copyright (C) 2004-2026  Thomas Okken
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see http://www.gnu.org/licenses/.
 *****************************************************************************/

#ifndef CORE_TABLES_H
#define CORE_TABLES_H 1


#include "free42.h"
#include "core_phloat.h"


/************/
/* Commands */
/************/

/* These are indices into cmd_array,
 * declared below (except the negative ones!)
 */

#define CMD_NONE         -1
#define CMD_CANCELLED    -2
#define CMD_LINGER1      -3
#define CMD_LINGER2      -4
#define CMD_CLX           0
#define CMD_ENTER         1
#define CMD_SWAP          2
#define CMD_RDN           3
#define CMD_CHS           4
#define CMD_DIV           5
#define CMD_MUL           6
#define CMD_SUB           7
#define CMD_ADD           8
#define CMD_LASTX         9
#define CMD_SILENT_OFF   10
#define CMD_SILENT_ON    11
#define CMD_SIN          12
#define CMD_COS          13
#define CMD_TAN          14
#define CMD_ASIN         15
#define CMD_ACOS         16
#define CMD_ATAN         17
#define CMD_LOG          18
#define CMD_10_POW_X     19
#define CMD_LN           20
#define CMD_E_POW_X      21
#define CMD_SQRT         22
#define CMD_SQUARE       23
#define CMD_INV          24
#define CMD_Y_POW_X      25
#define CMD_PERCENT      26
#define CMD_PI           27
#define CMD_COMPLEX      28
#define CMD_STO          29
#define CMD_STO_DIV      30
#define CMD_STO_MUL      31
#define CMD_STO_SUB      32
#define CMD_STO_ADD      33
#define CMD_RCL          34
#define CMD_RCL_DIV      35
#define CMD_RCL_MUL      36
#define CMD_RCL_SUB      37
#define CMD_RCL_ADD      38
#define CMD_FIX          39
#define CMD_SCI          40
#define CMD_ENG          41
#define CMD_ALL          42
#define CMD_NULL         43
#define CMD_ASTO         44
#define CMD_ARCL         45
#define CMD_CLA          46
#define CMD_DEG          47
#define CMD_RAD          48
#define CMD_GRAD         49
#define CMD_RECT         50
#define CMD_POLAR        51
#define CMD_SIZE         52
#define CMD_QUIET        53
#define CMD_CPXRES       54
#define CMD_REALRES      55
#define CMD_KEYASN       56
#define CMD_LCLBL        57
#define CMD_RDXDOT       58
#define CMD_RDXCOMMA     59
#define CMD_CLSIGMA      60
#define CMD_CLP          61
#define CMD_CLV          62
#define CMD_CLST         63
#define CMD_CLRG         64
#define CMD_DEL          65
#define CMD_CLKEYS       66
#define CMD_CLLCD        67
#define CMD_CLMENU       68
#define CMD_CLALLa       69
#define CMD_TO_DEG       70
#define CMD_TO_RAD       71
#define CMD_TO_HR        72
#define CMD_TO_HMS       73
#define CMD_TO_REC       74
#define CMD_TO_POL       75
#define CMD_IP           76
#define CMD_FP           77
#define CMD_RND          78
#define CMD_ABS          79
#define CMD_SIGN         80
#define CMD_MOD          81
#define CMD_SF           82
#define CMD_CF           83
#define CMD_FS_T         84
#define CMD_FC_T         85
#define CMD_FSC_T        86
#define CMD_FCC_T        87
#define CMD_COMB         88
#define CMD_PERM         89
#define CMD_FACT         90
#define CMD_GAMMA        91
#define CMD_RAN          92
#define CMD_SEED         93
#define CMD_LBL          94
#define CMD_RTN          95
#define CMD_INPUT        96
#define CMD_VIEW         97
#define CMD_AVIEW        98
#define CMD_XEQ          99
#define CMD_PROMPT      100
#define CMD_PSE         101
#define CMD_ISG         102
#define CMD_DSE         103
#define CMD_AIP         104
#define CMD_XTOA        105
#define CMD_AGRAPH      106
#define CMD_PIXEL       107
#define CMD_BEEP        108
#define CMD_TONE        109
#define CMD_MVAR        110
#define CMD_VARMENU     111
#define CMD_GETKEY      112
#define CMD_MENU        113
#define CMD_KEYG        114
#define CMD_KEYX        115
#define CMD_X_EQ_0      116
#define CMD_X_NE_0      117
#define CMD_X_LT_0      118
#define CMD_X_GT_0      119
#define CMD_X_LE_0      120
#define CMD_X_GE_0      121
#define CMD_X_EQ_Y      122
#define CMD_X_NE_Y      123
#define CMD_X_LT_Y      124
#define CMD_X_GT_Y      125
#define CMD_X_LE_Y      126
#define CMD_X_GE_Y      127
#define CMD_PRSIGMA     128
#define CMD_PRP         129
#define CMD_PRV         130
#define CMD_PRSTK       131
#define CMD_PRA         132
#define CMD_PRX         133
#define CMD_PRUSR       134
#define CMD_LIST        135
#define CMD_ADV         136
#define CMD_PRLCD       137
#define CMD_DELAY       138
#define CMD_PON         139
#define CMD_POFF        140
#define CMD_MAN         141
#define CMD_NORM        142
#define CMD_TRACE       143
#define CMD_SIGMAADD    144
#define CMD_SIGMASUB    145
#define CMD_GTO         146
#define CMD_END         147
#define CMD_NUMBER      148
#define CMD_STRING      149
#define CMD_RUN         150
#define CMD_SST         151
#define CMD_GTODOT      152
#define CMD_GTODOTDOT   153
#define CMD_STOP        154
#define CMD_NEWMAT      155
#define CMD_RUP         156
#define CMD_REAL_T      157
#define CMD_CPX_T       158
#define CMD_STR_T       159
#define CMD_MAT_T       160
#define CMD_DIM_T       161
#define CMD_ASSIGNa     162
#define CMD_ASSIGNb     163
#define CMD_ASGN01      164
#define CMD_ASGN02      165
#define CMD_ASGN03      166
#define CMD_ASGN04      167
#define CMD_ASGN05      168
#define CMD_ASGN06      169
#define CMD_ASGN07      170
#define CMD_ASGN08      171
#define CMD_ASGN09      172
#define CMD_ASGN10      173
#define CMD_ASGN11      174
#define CMD_ASGN12      175
#define CMD_ASGN13      176
#define CMD_ASGN14      177
#define CMD_ASGN15      178
#define CMD_ASGN16      179
#define CMD_ASGN17      180
#define CMD_ASGN18      181
#define CMD_ASGNn01     182
#define CMD_ASGNn02     183
#define CMD_ASGNn03     184
#define CMD_ASGNn04     185
#define CMD_ASGNn05     186
#define CMD_ASGNn06     187
#define CMD_ASGNn07     188
#define CMD_ASGNn08     189
#define CMD_ASGNn09     190
#define CMD_ASGNn10     191
#define CMD_ASGNn11     192
#define CMD_ASGNn12     193
#define CMD_ASGNn13     194
#define CMD_ASGNn14     195
#define CMD_ASGNn15     196
#define CMD_ASGNn16     197
#define CMD_ASGNn17     198
#define CMD_ASGNn18     199
#define CMD_ON          200
#define CMD_OFF         201
#define CMD_KEY1G       202
#define CMD_KEY2G       203
#define CMD_KEY3G       204
#define CMD_KEY4G       205
#define CMD_KEY5G       206
#define CMD_KEY6G       207
#define CMD_KEY7G       208
#define CMD_KEY8G       209
#define CMD_KEY9G       210
#define CMD_KEYn1G      211
#define CMD_KEYn2G      212
#define CMD_KEYn3G      213
#define CMD_KEYn4G      214
#define CMD_KEYn5G      215
#define CMD_KEYn6G      216
#define CMD_KEY1X       217
#define CMD_KEY2X       218
#define CMD_KEY3X       219
#define CMD_KEY4X       220
#define CMD_KEY5X       221
#define CMD_KEY6X       222
#define CMD_KEY7X       223
#define CMD_KEY8X       224
#define CMD_KEY9X       225
#define CMD_KEYn1X      226
#define CMD_KEYn2X      227
#define CMD_KEYn3X      228
#define CMD_KEYn4X      229
#define CMD_KEYn5X      230
#define CMD_KEYn6X      231
#define CMD_VMEXEC      232
#define CMD_VMSTO       233
#define CMD_SIGMAREG    234
#define CMD_SIGMAREG_T  235
#define CMD_CLD         236
#define CMD_ACOSH       237
#define CMD_ALENG       238
#define CMD_ALLSIGMA    239
#define CMD_AND         240
#define CMD_AOFF        241
#define CMD_AON         242
#define CMD_AROT        243
#define CMD_ASHF        244
#define CMD_ASINH       245
#define CMD_ATANH       246
#define CMD_ATOX        247
#define CMD_BASEADD     248
#define CMD_BASESUB     249
#define CMD_BASEMUL     250
#define CMD_BASEDIV     251
#define CMD_BASECHS     252
#define CMD_BEST        253
#define CMD_BINM        254
#define CMD_BIT_T       255
#define CMD_BST         256
#define CMD_CORR        257
#define CMD_COSH        258
#define CMD_CROSS       259
#define CMD_CUSTOM      260
#define CMD_DECM        261
#define CMD_DELR        262
#define CMD_DET         263
#define CMD_DIM         264
#define CMD_DOT         265
#define CMD_EDIT        266
#define CMD_EDITN       267
#define CMD_EXITALL     268
#define CMD_EXPF        269
#define CMD_E_POW_X_1   270
#define CMD_FCSTX       271
#define CMD_FCSTY       272
#define CMD_FNRM        273
#define CMD_GETM        274
#define CMD_GROW        275
#define CMD_HEXM        276
#define CMD_HMSADD      277
#define CMD_HMSSUB      278
#define CMD_I_ADD       279
#define CMD_I_SUB       280
#define CMD_INDEX       281
#define CMD_INSR        282
#define CMD_INTEG       283
#define CMD_INVRT       284
#define CMD_J_ADD       285
#define CMD_J_SUB       286
#define CMD_LINF        287
#define CMD_LINSIGMA    288
#define CMD_LN_1_X      289
#define CMD_LOGF        290
#define CMD_MEAN        291
#define CMD_NOT         292
#define CMD_OCTM        293
#define CMD_OLD         294
#define CMD_OR          295
#define CMD_PGMSLV      296
#define CMD_PGMINT      297
#define CMD_POSA        298
#define CMD_PUTM        299
#define CMD_PWRF        300
#define CMD_RCLEL       301
#define CMD_RCLIJ       302
#define CMD_RNRM        303
#define CMD_ROTXY       304
#define CMD_RSUM        305
#define CMD_SWAP_R      306
#define CMD_SDEV        307
#define CMD_SINH        308
#define CMD_SLOPE       309
#define CMD_SOLVE       310
#define CMD_STOEL       311
#define CMD_STOIJ       312
#define CMD_SUM         313
#define CMD_TANH        314
#define CMD_TRANS       315
#define CMD_UVEC        316
#define CMD_WMEAN       317
#define CMD_WRAP        318
#define CMD_X_SWAP      319
#define CMD_XOR         320
#define CMD_YINT        321
#define CMD_TO_DEC      322
#define CMD_TO_OCT      323
#define CMD_LEFT        324
#define CMD_UP          325
#define CMD_DOWN        326
#define CMD_RIGHT       327
#define CMD_PERCENT_CH  328
#define CMD_SIMQ        329
#define CMD_MATA        330
#define CMD_MATB        331
#define CMD_MATX        332
#define CMD_GOTOROW     333
#define CMD_GOTOCOLUMN  334
#define CMD_A_THRU_F    335
#define CMD_CLALLb      336
#define CMD_PGMSLVi     337
#define CMD_PGMINTi     338
#define CMD_VMSTO2      339
#define CMD_VMSOLVE     340
#define CMD_MAX         341
#define CMD_MIN         342
#define CMD_FIND        343
#define CMD_XROM        344
/* iPhone hardware support */
#define CMD_ACCEL       345
#define CMD_LOCAT       346
#define CMD_HEADING     347
/* HP-41 Time Module & CX Time */
#define CMD_ADATE       348
#define CMD_ATIME       349
#define CMD_ATIME24     350
#define CMD_CLK12       351
#define CMD_CLK24       352
#define CMD_DATE        353
#define CMD_DATE_PLUS   354
#define CMD_DDAYS       355
#define CMD_DMY         356
#define CMD_DOW         357
#define CMD_MDY         358
#define CMD_TIME        359
/* Intel Decimal Floating-Point Math Library: self-test */
#define CMD_FPTEST      360
/* Programming */
#define CMD_LSTO        361
#define CMD_SST_UP      362
#define CMD_SST_RT      363
#define CMD_YMD         364
#define CMD_GETKEY1     365
#define CMD_GETKEYA     366
#define CMD_LASTO       367
#define CMD_LCLV        368
#define CMD_TRY         369
#define CMD_TRYX        370
#define CMD_CATCH_T     371
#define CMD_PRTRACE     372
/* BASE enhancements */
#define CMD_SL          373
#define CMD_SR          374
#define CMD_ASR         375
#define CMD_SLN         376
#define CMD_SRN         377
#define CMD_ASRN        378
#define CMD_LJ          379
#define CMD_RJ          380
#define CMD_RL          381
#define CMD_RR          382
#define CMD_RLC         383
#define CMD_RRC         384
#define CMD_RLN         385
#define CMD_RRN         386
#define CMD_RLCN        387
#define CMD_RRCN        388
#define CMD_SB          389
#define CMD_CB          390
#define CMD_B_T         391
#define CMD_NUM_B       392
#define CMD_MASKL       393
#define CMD_MASKR       394
#define CMD_SC          395
#define CMD_CC          396
#define CMD_C_T         397
#define CMD_N_TO_BS     398
#define CMD_N_TO_BD     399
#define CMD_N_TO_BQ     400
#define CMD_N_TO_DS     401
#define CMD_N_TO_DD     402
#define CMD_N_TO_DQ     403
#define CMD_N_TO_PS     404
#define CMD_N_TO_PD     405
#define CMD_N_TO_PQ     406
#define CMD_BS_TO_N     407
#define CMD_BD_TO_N     408
#define CMD_BQ_TO_N     409
#define CMD_DS_TO_N     410
#define CMD_DD_TO_N     411
#define CMD_DQ_TO_N     412
#define CMD_PS_TO_N     413
#define CMD_PD_TO_N     414
#define CMD_PQ_TO_N     415
#define CMD_WSIZE       416
#define CMD_WSIZE_T     417
#define CMD_BSIGNED     418
#define CMD_BWRAP       419
#define CMD_BRESET      420
#define CMD_DECINT      421
#define CMD_BINSEP      422
#define CMD_OCTSEP      423
#define CMD_DECSEP      424
#define CMD_HEXSEP      425
/* Useful X-Fcn functions missing from the 42S */
#define CMD_ANUM        426
#define CMD_X_SWAP_F    427
#define CMD_RCLFLAG     428
#define CMD_STOFLAG     429
/* User-defined functions */
#define CMD_FUNC        430
#define CMD_ERRMSG      431
#define CMD_ERRNO       432
#define CMD_RTNYES      433
#define CMD_RTNNO       434
#define CMD_RTNERR      435
#define CMD_STRACE      436
/* Big Stack */
#define CMD_4STK        437
#define CMD_L4STK       438
#define CMD_NSTK        439
#define CMD_LNSTK       440
#define CMD_DEPTH       441
#define CMD_DROP        442
#define CMD_DROPN       443
#define CMD_DUP         444
#define CMD_DUPN        445
#define CMD_PICK        446
#define CMD_UNPICK      447
#define CMD_RDNN        448
#define CMD_RUPN        449
/* Miscellaneous */
#define CMD_NOP         450
#define CMD_FMA         451
#define CMD_PGMMENU     452
#define CMD_PMEXEC      453
#define CMD_PGMVAR      454
#define CMD_VARMNU1     455
#define CMD_MENU1       456
#define CMD_PARAMS      457
#define CMD_X2LINE      458
#define CMD_A2LINE      459
#define CMD_A2PLINE     460
#define CMD_RCOMPLX     461
#define CMD_PCOMPLX     462
#define CMD_RE          463
#define CMD_IM          464
#define CMD_CONJ        465
#define CMD_ARG         466
#define CMD_CAPS        467
#define CMD_MIXED       468
#define CMD_STATIC      469
#define CMD_DYNAMIC     470
#define CMD_SKIP        471
#define CMD_CPXMAT_T    472
#define CMD_TYPE_T      473
#define CMD_A_THRU_F_2  474
#define CMD_DROP_CANCL  475
#define CMD_PRREG       476
#define CMD_CSLD_T      477
#define CMD_C_LN_1_X    478
#define CMD_C_E_POW_X_1 479
#define CMD_GETMI       480
#define CMD_PUTMI       481
#define CMD_GETLI       482
#define CMD_PUTLI       483
#define CMD_LOCK        484
#define CMD_UNLOCK      485
#define CMD_IDENT       486
/* String & List Functions */
#define CMD_XSTR        487
#define CMD_XASTO       488
#define CMD_LXASTO      489
#define CMD_XVIEW       490
#define CMD_APPEND      491
#define CMD_EXTEND      492
#define CMD_SUBSTR      493
#define CMD_LENGTH      494
#define CMD_HEAD        495
#define CMD_REV         496
#define CMD_SORT        497
#define CMD_POS         498
#define CMD_S_TO_N      499
#define CMD_N_TO_S      500
#define CMD_NN_TO_S     501
#define CMD_IP_TO_S     502
#define CMD_C_TO_N      503
#define CMD_N_TO_C      504
#define CMD_LIST_T      505
#define CMD_NEWLIST     506
#define CMD_TO_LIST     507
#define CMD_FROM_LIST   508
/* Generalized Comparisons */
#define CMD_X_EQ_NN     509
#define CMD_X_NE_NN     510
#define CMD_X_LT_NN     511
#define CMD_X_GT_NN     512
#define CMD_X_LE_NN     513
#define CMD_X_GE_NN     514
#define CMD_0_EQ_NN     515
#define CMD_0_NE_NN     516
#define CMD_0_LT_NN     517
#define CMD_0_GT_NN     518
#define CMD_0_LE_NN     519
#define CMD_0_GE_NN     520
/* Statistics Sums */
#define CMD_SN          521
#define CMD_SX          522
#define CMD_SX2         523
#define CMD_SY          524
#define CMD_SY2         525
#define CMD_SXY         526
#define CMD_SLNX        527
#define CMD_SLNX2       528
#define CMD_SLNY        529
#define CMD_SLNY2       530
#define CMD_SLNXLNY     531
#define CMD_SXLNY       532
#define CMD_SYLNX       533
/* For Plus42 compatibility */
#define CMD_WIDTH       534
#define CMD_HEIGHT      535

#define CMD_SENTINEL    536


/* command_spec.argtype */

#define ARG_NONE      0 /* No argument */
#define ARG_VAR       1 /* Variable: num, stk, var, ind */
#define ARG_REAL      2 /* Variable: num, stk, var, ind; real scalars only */
#define ARG_NAMED     3 /* Variable: var, ind */
#define ARG_NUM9      4 /* num (0..9), ind */
#define ARG_NUM11     5 /* num (0..11), ind */
#define ARG_NUM99     6 /* num (0..99), ind */
#define ARG_COUNT     7 /* numeric-only (SIMQ, DEL, SIZE, LIST) */
#define ARG_FUNC      8 /* numeric-only, [0-4][0-4] (FUNC) */
#define ARG_LBL       9 /* Label: num, lclbl, global, ind */
#define ARG_CKEY     10 /* Key in custom menu */
#define ARG_MKEY     11 /* Key in programmable menu (KEYG/KEYX) */
#define ARG_PRGM     12 /* Alpha label (CATSECT_PGM) */
#define ARG_RVAR     13 /* Variable (real only) (MVAR, INTEG, SOLVE) */
#define ARG_MAT      14 /* Variable (matrix only) (EDITN, INDEX) */
#define ARG_M_STK    15 /* Matrix variable or stack (GETMI, PUTMI) */
#define ARG_L_STK    16 /* List variable or stack (GETLI, PUTLI) */
#define ARG_XSTR     17 /* Long string (XSTR) */
#define ARG_OTHER    18 /* Weirdos */


/* command_spec.flags */

#define FLAG_PRGM_ONLY 1  /* Only allowed in program mode (LBL, DEL, ...) */
#define FLAG_IMMED     2  /* Executes in program mode (DEL, GTO.nnn, ...) */
#define FLAG_HIDDEN    4  /* Cannot be activated using XEQ "NAME" (SIMQ, ...) */
#define FLAG_NO_PRGM   8  /* Cannot be programmed (SIMQ, MATA, ...) */
#define FLAG_NO_SHOW  16  /* Do not show after keytimeout1 */
#define FLAG_SPECIAL  32  /* hp42s_code flags 0x01 */
#define FLAG_ILLEGAL  64  /* hp42s_code flags 0x02 */


/* Builtin cmd arg types */

/* These represent data types used when a command
 * is executing. Compare the ARG_ macros; those
 * represent the data types that a command is *capable*
 * of accepting, and are used during command entry.
 */

#define ARGTYPE_NONE      0
#define ARGTYPE_NUM       1
#define ARGTYPE_NEG_NUM   2 /* Used internally */
#define ARGTYPE_STK       3
#define ARGTYPE_STR       4
#define ARGTYPE_IND_NUM   5
#define ARGTYPE_IND_STK   6
#define ARGTYPE_IND_STR   7
#define ARGTYPE_LCLBL     9
#define ARGTYPE_DOUBLE   10
#define ARGTYPE_LBLINDEX 11
#define ARGTYPE_XSTR     12


struct arg_struct {
    unsigned char type;
    unsigned short length;
    int4 target;
    union {
        int4 num;
        char text[15];
        char stk;
        int cmd; /* For backward compatibility only! */
        char lclbl;
        const char *xstr;
    } val;
    // This used to be a member of the 'val' union, but once I changed it
    // from 'double' to 'phloat', that was no longer possible.
    phloat val_d;
};


struct command_spec {
    int (*handler)(arg_struct *arg);
    const char *name;
    unsigned char flags;
    unsigned char scode;
    unsigned char code1;
    unsigned char code2;
    unsigned char name_length;
    unsigned char argtype;
    signed char argcount : 7;
    bool listable : 1;
    unsigned char rttypes;
};

extern const command_spec cmd_array[];

int handle(int cmd, arg_struct *arg);


#endif
