//---------------------------------------------------------------------------
/*
	TJS2 Script Engine
	Copyright (C) 2000-2004  W.Dee <dee@kikyou.info>

	See details of license at "license.txt"
*/
//---------------------------------------------------------------------------
// Japanese localized messages
//---------------------------------------------------------------------------
// 2004/ 5/16 W.Dee
//   警告用メッセージと後置!演算子用のメッセージを追加
//---------------------------------------------------------------------------

TJS_MSG_DECL(TJSInternalError, "内部エラーが発生しました")
TJS_MSG_DECL(TJSWarning, "警告: ")
TJS_MSG_DECL(TJSWarnEvalOperator, "グローバルでない場所で後置 ! 演算子が使われています(この演算子の挙動はTJS2 version 2.4.1 で変わりましたのでご注意ください)")
TJS_MSG_DECL(TJSNarrowToWideConversionError, "ANSI 文字列を UNICODE 文字列に変換できません");
TJS_MSG_DECL(TJSVariantConvertError, "%1 から %2 へ型を変換できません")
TJS_MSG_DECL(TJSIDExpected, "識別子を指定してください")
TJS_MSG_DECL(TJSCannotModifyLHS, "不正な代入か不正な式の操作です")
TJS_MSG_DECL(TJSInsufficientMem, "メモリが足りません")
TJS_MSG_DECL(TJSCannotGetResult, "この式からは値を得ることができません")
TJS_MSG_DECL(TJSNullAccess, "null オブジェクトにアクセスしようとしました")
TJS_MSG_DECL(TJSMemberNotFound, "メンバ \"%1\" が見つかりません")
TJS_MSG_DECL(TJSMemberNotFoundNoNameGiven, "メンバが見つかりません")
TJS_MSG_DECL(TJSNotImplemented, "呼び出そうとした機能は未実装です")
TJS_MSG_DECL(TJSInvalidParam, "不正な引数です")
TJS_MSG_DECL(TJSBadParamCount, "引数の数が不正です")
TJS_MSG_DECL(TJSInvalidType, "関数ではないかプロパティの種類が違います")
TJS_MSG_DECL(TJSSpecifyDicOrArray, "Dictionary または Array クラスのオブジェクトを指定してください");
TJS_MSG_DECL(TJSStringDeallocError, "文字列メモリブロックを解放できません")
TJS_MSG_DECL(TJSStringAllocError, "文字列メモリブロックを確保できません")
TJS_MSG_DECL(TJSMisplacedBreakContinue, "\"break\" または \"continue\" はここに書くことはできません")
TJS_MSG_DECL(TJSMisplacedCase, "\"case\" はここに書くことはできません")
TJS_MSG_DECL(TJSMisplacedReturn, "\"return\" はここに書くことはできません")
TJS_MSG_DECL(TJSStringParseError, "文字列定数/正規表現/オクテット即値が終わらないままスクリプトの終端に達しました")
TJS_MSG_DECL(TJSNumberError, "数値として解釈できません")
TJS_MSG_DECL(TJSUnclosedComment, "コメントが終わらないままスクリプトの終端に達しました")
TJS_MSG_DECL(TJSInvalidChar, "不正な文字です : \'%1\'")
TJS_MSG_DECL(TJSExpected, "%1 がありません")
TJS_MSG_DECL(TJSSyntaxError, "文法エラーです(%1)")
TJS_MSG_DECL(TJSPPError, "条件コンパイル式にエラーがあります")
TJS_MSG_DECL(TJSCannotGetSuper, "スーパークラスが存在しないかスーパークラスを特定できません")
TJS_MSG_DECL(TJSInvalidOpecode, "不正な VM コードです")
TJS_MSG_DECL(TJSRangeError, "値が範囲外です")
TJS_MSG_DECL(TJSAccessDenyed, "読み込み専用あるいは書き込み専用プロパティに対して行えない操作をしようとしました")
TJS_MSG_DECL(TJSNativeClassCrash, "実行コンテキストが違います")
TJS_MSG_DECL(TJSInvalidObject, "オブジェクトはすでに無効化されています")
TJS_MSG_DECL(TJSDuplicatedPropHandler, "\"setter\" または \"getter\" が重複しています")
TJS_MSG_DECL(TJSCannotOmit, "\"...\" は関数外では使えません")
TJS_MSG_DECL(TJSCannotParseDate, "不正な日付文字列の形式です")
TJS_MSG_DECL(TJSInvalidValueForTimestamp, "不正な日付・時刻です")
TJS_MSG_DECL(TJSExceptionNotFound, "\"Exception\" が存在しないため例外オブジェクトを作成できません")
TJS_MSG_DECL(TJSInvalidFormatString, "不正な書式文字列です")
TJS_MSG_DECL(TJSDivideByZero, "0 で除算をしようとしました")
TJS_MSG_DECL(TJSNotReconstructiveRandomizeData, "乱数系列を初期化できません(おそらく不正なデータが渡されました)")
TJS_MSG_DECL(TJSSymbol, "識別子")
TJS_MSG_DECL(TJSWriteError, "書き込みエラーが発生しました")
TJS_MSG_DECL(TJSReadError, "読み込みエラーが発生しました")
TJS_MSG_DECL(TJSSeekError, "シークエラーが発生しました")
//---------------------------------------------------------------------------
