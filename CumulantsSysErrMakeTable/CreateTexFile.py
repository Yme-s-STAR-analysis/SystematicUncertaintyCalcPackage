class ReplaceTool:
    eng = "7.7"
    mapping_netp = {
        "C1": r"$C_{1}$",
        "C2": r"$C_{2}$",
        "C3": r"$C_{3}$",
        "C4": r"$C_{4}$",
        "R21": r"$C_{2}/C_{1}$",
        "R32": r"$C_{3}/C_{2}$",
        "R2s": r"$C_{2}/\langle <p+\bar{p}\rangle$",
        "R31": r"$C_{3}/C_{1}$",
        "R42": r"$C_{4}/C_{2}$",
    }
    mapping_p = {
        "C1": r"$C_{1}$",
        "C2": r"$C_{2}$",
        "C3": r"$C_{3}$",
        "C4": r"$C_{4}$",
        "R21": r"$C_{2}/C_{1}$",
        "R31": r"$C_{3}/C_{1}$",
        "R42": r"$C_{4}/C_{2}$",
        "k1": r"$\kappa_{1}$",
        "k2": r"$\kappa_{2}$",
        "k3": r"$\kappa_{3}$",
        "k4": r"$\kappa_{4}$",
        "k21": r"$\kappa_{2}/\kappa_{1}$",
        "k31": r"$\kappa_{3}/\kappa_{1}$",
        "k41": r"$\kappa_{4}/\kappa_{1}$",
    }
    mapping = {
        "C1": r"$C_{1}$",
        "C2": r"$C_{2}$",
        "C3": r"$C_{3}$",
        "C4": r"$C_{4}$",
        "R21": r"$C_{2}/C_{1}$",
        "R2s": r"$C_{2}/\langle p+\bar{p}\rangle$",
        "R31": r"$C_{3}/C_{1}$",
        "R1s": r"$C_{3}/\langle p+\bar{p}\rangle$",
        "R32": r"$C_{3}/C_{2}$",
        "R42": r"$C_{4}/C_{2}$",
        "k1": r"$\kappa_{1}$",
        "k2": r"$\kappa_{2}$",
        "k3": r"$\kappa_{3}$",
        "k4": r"$\kappa_{4}$",
        "k21": r"$\kappa_{2}/\kappa_{1}$",
        "k31": r"$\kappa_{3}/\kappa_{1}$",
        "k41": r"$\kappa_{4}/\kappa_{1}$",
    }
    yTags = {
        "y0p1": r"$|y|<0.1$",
        "y0p2": r"$|y|<0.2$",
        "y0p3": r"$|y|<0.3$",
        "y0p4": r"$|y|<0.4$",
        "y0p6": r"$|y|<0.6$",
    }
    ptFix = r"$0.4<p_\mathrm{{T}}<2.0$ GeV/c"
    ptTags = {
        "pt0p8": r"$0.4<p_\mathrm{{T}}<0.8$ GeV/c",
        "pt1p0": r"$0.4<p_\mathrm{{T}}<1.0$ GeV/c",
        "pt1p2": r"$0.4<p_\mathrm{{T}}<1.2$ GeV/c",
        "pt1p4": r"$0.4<p_\mathrm{{T}}<1.4$ GeV/c",
        "pt1p6": r"$0.4<p_\mathrm{{T}}<1.6$ GeV/c",
        "pt1p8": r"$0.4<p_\mathrm{{T}}<1.8$ GeV/c",
    }
    yFix = r"$|y|<0.5$"
    # eq_ref = r"~\ref{eq:new_sys_calc_single_source}"

    # def ReplaceCaption(self, cum_tag: str, withX: str, p_tag: str = "net-proton"):
    def ReplaceCaption(self, cum_tag: str, p_tag: str = "net-proton", scanCode: str = "y0p5"):
        assert(cum_tag in self.mapping)
        # assert(withX in ["3", "3X"])

        if p_tag == 'net-proton':
            mapping = self.mapping_netp
        elif p_tag in ['proton', 'antiproton']:
            mapping = self.mapping_p
        else:
            mapping = self.mapping
        # return f'\caption{{Detailed systematic uncertainty of {p_tag} {mapping[cum_tag]} from {self.eng} data set. Those systematic differences which did not pass Barlow check will be marked in red. This table shows the results with centrality defined with RefMult{withX}.}}\n'
        scanText = ''
        if scanCode[0] == "y":
            scanText = f'within {self.ptFix} and {self.yTags[scanCode]}.'
        elif scanCode[0] == "p":
            scanText = f'within {self.ptTags[scanCode]} and {self.yFix}.'
        return f'\caption{{Systematic uncertainty of {p_tag} {mapping[cum_tag]} from Au+Au collisions at \snn$={self.eng}$ GeV {scanText}}}\n'
    
    # def ReplaceLabel(self, cum_tag: str, withX: str, p_tag: str = 'netp'):
    def ReplaceLabel(self, cum_tag: str, p_tag: str = 'netp', scanCode: str = "y0p5"):
        assert(cum_tag in self.mapping)
        # assert(withX in ["3", "3X"])
        return f'\label{{tab:{cum_tag}_{p_tag}_{scanCode}}}\n'
    
    def Make(self, fname: str, cum_tag: str, p_tag: str = 'net-proton', scanCode: str = "y0p5"):
        # get the actual file name
        splits = fname.split('/')
        with open(fname, 'r') as f:
            l = f.readlines()
        fname = '/'.join(splits[:-1] + [f'Rep{splits[-1]}'])
        pTagMap = {
            "net-proton": "Netp",
            "proton": "Pro",
            "antiproton": "Pbar"
        }
        with open(fname, 'w') as f:
            for item in l:
                if item.strip() == r'\begin{table}[]':
                    f.write(r'\begin{table}[!h]')
                    f.write('\n')
                    f.write('\centering')
                    f.write('\n')
                elif item[1:8] == 'caption':
                    f.write(self.ReplaceCaption(cum_tag, p_tag, scanCode))
                elif item[1:6] == 'label':
                    f.write(self.ReplaceLabel(cum_tag, p_tag, scanCode))
                elif item.strip() == r'\end{table}':
                    f.write(item)
                    # add the figures
                    s = r'''
\begin{{minipage}}[t]{{0.48\textwidth}}
  \centering
  \includegraphics[width=\linewidth]{{../barlow/Barlow_{}_{}_{}_cent0X.pdf}}
\end{{minipage}}
\hfill
\begin{{minipage}}[t]{{0.48\textwidth}}
  \centering
  \includegraphics[width=\linewidth]{{../cplot/Contr_{}_{}_{}_cent0X.pdf}}
\end{{minipage}}
'''.format(pTagMap[p_tag], cum_tag, scanCode, pTagMap[p_tag], cum_tag, scanCode)
                    f.write(s)
                    f.write('\n')
                else:
                    f.write(item)
        return fname

    def TexFileDescription(self, scanCode: str = "rapidity"):
        return f'The systematic uncertainty of {scanCode} scan from Au+Au collisions at \snn$={self.eng}$ GeV.\n'


# here is main
if __name__ == '__main__': 

    DocumentHader = r"""
\documentclass{article}  
\usepackage{array}        
\usepackage{booktabs}     
\usepackage{multirow}     
\usepackage{caption}      
\usepackage{longtable}    
\usepackage{geometry}     
\usepackage{graphicx}     
\usepackage{colortbl}     
\usepackage[table]{xcolor}

\begin{document}

\newcommand{\snn}{$\sqrt{s_\mathrm{NN}}$}

    """

    concate = True # if you want to get a looooong text file with all tables combined
    ycat_name = '../table/y_Concated.tex'
    ptcat_name = '../table/pt_Concated.tex'
    rt = ReplaceTool()
    ptypes = ['Netp', 'Pro', 'Pbar']
    fitems_netp = [
        'C1', 'C2', 'C3', 'C4', 'R21', 'R32', 'R42', 'R2s', 'R31'
    ]
    fitems_p = [
        'k1', 'k2', 'k3', 'k4', 'k21', 'k31', 'k41'
    ]
    y_outnames = []
    pt_outnames = []
    for scanTag in ['y0p1', 'y0p2', 'y0p3', 'y0p4', 'y0p6', 'pt0p8', 'pt1p0', 'pt1p2', 'pt1p4', 'pt1p6', 'pt1p8']:
        for p in ptypes:
            p_tag = '?'
            if p == 'Netp':
                p_tag = 'net-proton'
                fnamesX = [f'../table/{p}_{item}_{scanTag}X.txt' for item in fitems_netp]
                for item, nameX in zip(fitems_netp, fnamesX):
                    if scanTag[0] == 'y':
                        y_outnames.append(rt.Make(nameX, item, p_tag, scanTag))
                    else:
                        pt_outnames.append(rt.Make(nameX, item, p_tag, scanTag))
            elif p == 'Pro':
                p_tag = 'proton'
                fnamesX = [f'../table/{p}_{item}_{scanTag}X.txt' for item in fitems_p]
                for item, nameX in zip(fitems_p, fnamesX):
                    if scanTag[0] == 'y':
                        y_outnames.append(rt.Make(nameX, item, p_tag, scanTag))
                    else:
                        pt_outnames.append(rt.Make(nameX, item, p_tag, scanTag))
            elif p == 'Pbar':
                p_tag = 'antiproton'
                fnamesX = [f'../table/{p}_{item}_{scanTag}X.txt' for item in fitems_p]
                for item, nameX in zip(fitems_p, fnamesX):
                    if scanTag[0] == 'y':
                        y_outnames.append(rt.Make(nameX, item, p_tag, scanTag))
                    else:
                        pt_outnames.append(rt.Make(nameX, item, p_tag, scanTag))

    if concate:
        for cat_name, texdes, outnames in zip([ycat_name, ptcat_name], ["rapidity", "transverse momentum"], [y_outnames, pt_outnames]):
            with open(cat_name, 'w') as f:
                f.write(DocumentHader)
                f.write(rt.TexFileDescription(texdes))
                for subfile_name in outnames:
                    for line in open(subfile_name):
                        f.writelines(line)
                    f.write('\n\\clearpage\n')
                f.write("\n\\end{document}\n")
