# hakoniwa-sumo

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
# Hakoniwa Ko-Ekiden 2 (English)

## Project Status and Open Sourcing
Thank you for your interest in "Hakoniwa Ko-Ekiden 2".
I, the original author (Shin Tomura), have decided to step away from any future development and maintenance of this project.

I am open-sourcing all resources with the hope that the code and assets I have cultivated will be useful to those learning game development or wanting to implement new ideas. I am completely entrusting the future of this project to the community. Please feel free to fork, modify, and redistribute it.

## Repository Contents
To keep the repository lightweight, it contains only the following:
* The game's source code (2 files)
* The `release` folder (execution assets published on platforms like Steam)

## Build Instructions
This project was developed using the "DX Library" (a Japanese game development framework). However, the DX Library itself is NOT included in this repository.
To compile and build the game from source, you will need to download the DX Library from the official website below and set it up in your development environment (such as Visual Studio).

* DX Library Official Website: https://dxlib.xsrv.jp/ (Japanese only)

## License and Assets
This project is licensed under the **MIT License**.

All assets contained in the `release` folder—including images, audio, and **all 3D MMD models and motion data used for the runners**—are 100% original, created entirely from scratch by me without using any third-party materials.
Therefore, **everything in this repository, including both the source code and the asset data, is fully covered by the MIT License**. You are free to use them for both commercial and non-commercial purposes.

Please note that the compiled, ready-to-play version of the game remains available for free on Steam.
