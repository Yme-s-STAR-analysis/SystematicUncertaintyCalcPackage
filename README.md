# Systematic Uncertainty Calculation Package

* Author: Yige Huang

* Data: 13.05.2024

* Version: 2.13

## How to Use

### The format of ROOT files

1. The ROOT file should store net-proton, proton and antiproton cumulants, factorial cumulants and ratios.

2. The objects should be `TGraphErrors`, X-axis is `Npart` and Y-axis is observable, the order should be from most central to peripheral, in total 9 points (centralities).

    e.g. x[0] = 340.0, xerr[0] = 0.0, y[0] = 7.77, yerr[0] = 0.4396

3. The name of objects should be `A_B`, like: `Netp_C1`

    `A` can be one of `Netp`, `Pro` and `Pbar`

    `B` can be (factorial) cumulants: `C1` to `C6`, `k1` to `k6`

    `B` can also be cumulant ratios: `R21`, `R32`, `R42`, `R51`, `R62`

    `B` can also be factorial cumulant ratios: `k21` to `k61`

### The path to ROOT files

To make it easier to use, you'd better follow the rule of saving ROOT file and follow the instructions:

1. Select a `root path`, like `/user/yourname/analysis/cumulants/roots`, and put this `root path` into `CumulantsSysErrMakeTable/doXXX.sh`'s `FPATH`

2. Put your root files into a sub-folder names as `TAG.coll/cum.cbwc.TAG.SCAN.vz0.root`

    `TAG` is used to classify the cuts, and its name is indeed not important

    `SCAN` is the rapidity or pT scan tag, it's also not important

    `vz0` is for RefMult3, and `vz0X` is for RefMult3X

### Configurations in the scripts

Modifying `main.cxx` is taken as an example:

1. Line 41 and 42: change number of sources and (maximum) number of cuts from sources

2. Line 50: name of sources (to be shown in the table), note that one should use `\` properly

3. Line 54 to 59: name of cuts (to be shown in the table)

4. Line 62 to 67: as mentioned in former part (*The path to ROOT files*), put the corresponding `TAG` names here

5. Line 69: the number of cuts that are really used from each source

6. Line 78: replace the first argument of `gl->GetPoint` with your default cut's `TAG`

### How to run

1. `make run`

2. `mkdir ../tables`

3. Set `FPATH` in `doGetSysErr.sh`

4. Run it using z shell: `zsh doGetSysErr.sh`

    If you are not using z shell, it's also possible to do this mannually instead of using a script

## Guide

* Folders

1. `core`: Definitions and implements for base classes, including `Point`, `Source` and `System`, also a `FormatSystem` class for output a `LATEX` table.

2. `demo`: Some demos, enter this directory and `make` to have a quick experience.

3. `CumulantsSysErrMakeTable`: MUST use Yige's format of saving cumulant results. Indeed, is a larger demo of using this systematic uncertainty calculation package.

* How to run

1. See `demo` and `CumulantsSysErrMakeTable`.

2. `CumulantsSysErrMakeTable` shows a complecated usage, for beginners, please see `demo/testFormat.cxx` and follow this guide:

    > Initilize points `Point` with value, error and tag. You need a default point, and many varied points.
    >
    > Initilize sources `Source` with many points. For each source, a default point is needed with `Source::SetDefault`, and varied points are also necessary with `Source::AddVaried`.
    >
    > After you have all the sources prepared, add them to the `System`. Using `System::AddSource`.
    >
    > The `FormatSystem` class can make a LATEX table with 9 centrality points, which means you will need to prepare 9 `System` instances and add them to the `FormatSystem` with `Formatsystem::LoadSystem`.
    >
    > When everything above is done, use `FormatSystem::Print` to save the code of LATEX table.

3. The documents of this package are not yet finished, will get it updated soon.

## Notes

1. Before you output the LATEX table, please remember to call `System::GetSigma`. Then system-wise, source-wise and point-wise errors will all got calculated.

2. You can choose to turn on or turn off Barlow check (source level), please use `Source(const char*, int, bool)` constructor instead of `Source()`.

3. The output format can be changed with `FormatSystem::SetFormat`, the default argument is `%.4f`.

## Patch Notes

13.05.2024 by yghuang v2.13:

> Update: ROOT file generator, to customize mean Npart value of each bin
>
> Remove: gamma (PID efficiency mode) term in systematic uncertainty calculation
>
> Add: multiplicity bin term in systematic uncertainty calculation

(v2.13.1):

> Fix some bugs and typoes

07.05.2024 by yghuang v2.12:

> Updated LATEX table style: add borders and scale (default value 0.6)

28.04.2024 by yghuang v2.11:

> Add a detailed users' guide

23.04.2024 yghuang v2.10:

> Fix a text bug in table text replacing script, C2/C2 -> C2/C1
>
> Updated bacth scripts

15.04.2024 yghhuang v2.9:

> Add template of contribution plot that shows the fraction of each systematic sources

08.02.2024 yghuang v2.8:

> Update the formula of a systematic uncertainty for a source
>
>> Now we only devide by n (passed Barlow check) instead of n (all changed cuts)
>
> Updated DiffPlot and RootFile generator

07.02.2024 yghuang v2.7:

> Updated: LATEX table generator, and a python script for generating a concated LATEX code

06.02.2024 yghuang v2.6:

> Updated: LATEX table generator

27.01.2024 yghuang v2.5:

> Updated: LATEX table generator

17.01.2024 yghuang v2.4:

> Updated: Difference plot for systematic uncertainty cuts (those who passed Barlow check or not)
>
> Updated: LATEX table generator

23.06.2023 yghuang v2.2:

> New feature: make the plot of a variable with selected centrality. See MakeDiffPlot.

20.06.2023 yghuang v2.1:

> Now the LATEX table will also show the systematic difference as RED text if this cut did not pass the Barlow Check.
> Accordingly, the core codes are changed.

14.06.2023 yghuang v2.0:

> The barlow check part is incorrect, now fixed.

13.05.2023 yghuang v1.1:

> New feature: not only ouput LATEX table codes, but also create root files.

13.05.2023 yghuang v1.0:

> First version, all the fundamental functions are implemented.
