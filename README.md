# 箱庭小相撲 (Hakoniwa Sumo)

[English follows Japanese](#english)

## プロジェクトの現状とオープンソース化について
「箱庭小相撲」をご愛顧いただきありがとうございます。5年以上このゲームの開発作業から遠ざかってしまいました。
残念ながら英語対応したバージョンのリソースは消失してしまいましたが、英語対応する前の日本語だけのバージョンのものは奇跡的に残っていましたので、すべてのリソースをオープンソースとして公開します。フォーク、改変、再配布など、自由にご活用ください。

## リポジトリの内容
リポジトリを軽量に保つため、本リポジトリには以下のデータのみが含まれています。
* ゲームのソースコード（`src` フォルダ）
* `release` フォルダ（実行用アセット群）

## ビルドに関する注意事項
本プロジェクトは「DXライブラリ」を使用して開発されていますが、DXライブラリ本体は本リポジトリに同梱されていません。
ソースコードからコンパイル・ビルドを行う場合は、ご自身で以下の公式サイトからDXライブラリをダウンロードし、開発環境（Visual Studio等）へのセットアップをお願いいたします。

* DXライブラリ公式サイト: https://dxlib.xsrv.jp/

## ライセンスとアセットについて
本プロジェクトは **MIT License** の下で公開されています。

`release` フォルダに含まれる画像や音楽は外部素材を一切使用せず、私自身がゼロから作成した完全なオリジナルデータです。
したがって、ソースコードだけでなくこれらのアセットデータも含めた**リポジトリ内の全データがMITライセンスの対象**となります。商用・非商用問わず、ご自由にお使いいただけます。

なお、コンパイル済みの英語にも対応したバージョンの完成版ゲームはSteam等にて無料で公開し続けていますので、遊ぶだけであればそちらをご利用ください。

---

<a id="english"></a>
# Hakoniwa Sumo (English)

**Note:** The source code and assets provided here are based on the original Japanese version. There is no English localization included in this repository.

The compiled, ready-to-play version of the game (which supports English) remains available for free on Steam. Please use that version if you only wish to play the game.

## Current Project Status and Open Sourcing
Thank you for your continued support of "Hakoniwa Sumo." It has been over five years since I was last active in the development of this game. 
Unfortunately, the resources for the English-localized version have been lost. However, the original Japanese-only version miraculously survived, so I am releasing all of its resources as open-source. Please feel free to fork, modify, and redistribute it.

## Repository Content
To keep the repository lightweight, it only contains the following:
* **`src` folder**: Game source code.
* **`release` folder**: Assets required for execution.

## Build Instructions
This project was developed using the **DX Library**. The library itself is not included in this repository. 
If you wish to compile or build the game from the source code, please download the DX Library from the official website and set it up in your development environment (such as Visual Studio).

* **DX Library Official Site**: [https://dxlib.xsrv.jp/](https://dxlib.xsrv.jp/)

## License and Assets
This project is licensed under the **MIT License**.

All images and music found in the `release` folder are completely original works created by me from scratch. No external materials were used. Therefore, **all data within this repository—including both the source code and the assets—is subject to the MIT License.** You are free to use them for both commercial and non-commercial purposes.
