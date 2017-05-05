# プログレスダイアログの実装

キャンセル可能な処理と、それを呼び出し、進行中にはプログレスバーを表示するクラス群を定義します。

## 制約事項

- VS2013で作成したプロジェクトです。
- C++-11の非同期処理機能 (`std::async`, `std::future`) を使っています。
- 処理完了後にプログレスダイアログを閉じさせるために、独自のメッセージ(`WM_CLOSE_PROGRESS_DIALOG`)を定義しています → `stdafx.h`

## 設計

- [クラス図・シーケンス図](https://asura.github.io/progress_dialog/)
- コンセプト実装部分 (流用するもの)
  - `ICancelable`
  - `CancelableProcessBase`
  - `CProgressDialog`
- サンプル実装部分 (捨てて良いもの)
  - `ConcreteProcess`
  - `CProgressDialogDlg`
  - `CProgressDialogApp`

## 利用方法

1. `CancelableProcessBase`から派生させた処理クラスを定義する
1. 上記派生クラスの`DoImpl()`メソッドを実装する (適宜`ShouldCancel()`を使い、UI側からキャンセル要求が来ていないか確認すること)
1. 処理させたいタイミングで、上記クラスのインスタンスを生成する
1. `CProgressDialog`クラスのインスタンスを生成する (コンストラクタに、上記インスタンスを渡す)
1. `DoModal()`する
1. `DoModal()`の戻り値が`IDOK`かどうかにより、正常終了 or 異常終了に対応した後処理を実行する

## 参考にしたサイト

- [packaged_taskについて - yohhoyの日記](http://d.hatena.ne.jp/yohhoy/20120202/p1)
- [C++スレッド遅延開始の実装5パターン - yohhoyの日記（別館）](http://yohhoy.hatenablog.jp/entry/2012/04/20/140749)