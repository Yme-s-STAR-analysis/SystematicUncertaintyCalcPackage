r'''
    Table Caption Replace Scripts
    By Yige Huang
    14.05.2024
    Patch: 1.1
'''

class ReplaceTool:
    eng = "DATASET GeV"
    mapping_netp = {
        "C1": r"$C_{1}$",
        "C2": r"$C_{2}$",
        "C3": r"$C_{3}$",
        "C4": r"$C_{4}$",
        "R2s": r"$C_{2}$/$\left<p+\bar{p}\right>$",
        "R31": r"$C_{3}$/$C_{1}$",
        "R42": r"$C_{4}$/$C_{2}$",
    }
    mapping_p = {
        "C1": r"$C_{1}$",
        "C2": r"$C_{2}$",
        "C3": r"$C_{3}$",
        "C4": r"$C_{4}$",
        "R21": r"$C_{2}$/$C_{1}$",
        "R31": r"$C_{3}$/$C_{1}$",
        "R42": r"$C_{4}$/$C_{2}$",
        "k1": r"$\kappa_{1}$",
        "k2": r"$\kappa_{2}$",
        "k3": r"$\kappa_{3}$",
        "k4": r"$\kappa_{4}$",
        "k21": r"$\kappa_{2}$/$\kappa_{1}$",
        "k31": r"$\kappa_{3}$/$\kappa_{1}$",
        "k41": r"$\kappa_{4}$/$\kappa_{1}$",
    }
    mapping = {
        "C1": r"$C_{1}$",
        "C2": r"$C_{2}$",
        "C3": r"$C_{3}$",
        "C4": r"$C_{4}$",
        "R21": r"$C_{2}$/$C_{1}$",
        "R2s": r"$C_{2}$/$\left<p+\bar{p}\right>$",
        "R31": r"$C_{3}$/$C_{1}$",
        "R1s": r"$C_{3}$/$\left<p+\bar{p}\right>$",
        "R32": r"$C_{3}$/$C_{2}$",
        "R42": r"$C_{4}$/$C_{2}$",
        "k1": r"$\kappa_{1}$",
        "k2": r"$\kappa_{2}$",
        "k3": r"$\kappa_{3}$",
        "k4": r"$\kappa_{4}$",
        "k21": r"$\kappa_{2}$/$\kappa_{1}$",
        "k31": r"$\kappa_{3}$/$\kappa_{1}$",
        "k41": r"$\kappa_{4}$/$\kappa_{1}$",
    }
    eq_ref = r"~\ref{eq:new_sys_calc_single_source}"

    def ReplaceCaption(self, cum_tag: str, withX: str, p_tag: str = "net-proton"):
        assert(cum_tag in self.mapping)
        assert(withX in ["3", "3X"])

        if p_tag == 'net-proton':
            mapping = self.mapping_netp
        elif p_tag in ['proton', 'antiproton']:
            mapping = self.mapping_p
        else:
            mapping = self.mapping
        return f'\caption{{Detailed systematic uncertainty of {p_tag} {mapping[cum_tag]} from {self.eng} data set. Those systematic differences which did not pass Barlow check will be marked in red. This table shows the results with centrality defined with RefMult{withX}.}}\n'
    
    def ReplaceLabel(self, cum_tag: str, withX: str, p_tag: str = 'netp'):
        assert(cum_tag in self.mapping)
        assert(withX in ["3", "3X"])
        return f'\label{{tab:{cum_tag}_RefMult{withX}_{p_tag}}}\n'
    
    def Make(self, fname: str, cum_tag: str, withX: str, p_tag: str = 'net-proton'):
        # get the actual file name
        splits = fname.split('/')
        with open(fname, 'r') as f:
            l = f.readlines()
        fname = '/'.join(splits[:-1] + [f'Rep{splits[-1]}'])
        with open(fname, 'w') as f:
            for item in l:
                if item[1:8] == 'caption':
                    f.write(self.ReplaceCaption(cum_tag, withX, p_tag))
                elif item[1:6] == 'label':
                    f.write(self.ReplaceLabel(cum_tag, withX, p_tag))
                else:
                    f.write(item)
        return fname

# here is main
if __name__ == '__main__': 
    concate = True # if you want to get a looooong text file with all tables combined
    cat_name = '../table/Concated.txt'
    rt = ReplaceTool()
    ptypes = ['Netp', 'Pro', 'Pbar']
    fitems_netp = [
        'C1', 'C2', 'C3', 'C4', 'R2s', 'R31', 'R42'
    ]
    fitems_p = [
        'C1', 'C2', 'C3', 'C4', 'R21', 'R31', 'R42',
        'k1', 'k2', 'k3', 'k4', 'k21', 'k31', 'k41'
    ]
    outnames = []
    for p in ptypes:
        p_tag = '?'
        if p == 'Netp':
            p_tag = 'net-proton'
            fnames = [f'../table/{p}_{item}_y0p5.txt' for item in fitems_netp]
            fnamesX = [f'../table/{p}_{item}_y0p5X.txt' for item in fitems_netp]
            for item, name, nameX in zip(fitems_netp, fnames, fnamesX):
                outnames.append(rt.Make(name, item, '3', p_tag))
                outnames.append(rt.Make(nameX, item, '3X', p_tag))
        elif p == 'Pro':
            p_tag = 'proton'
            fnames = [f'../table/{p}_{item}_y0p5.txt' for item in fitems_p]
            fnamesX = [f'../table/{p}_{item}_y0p5X.txt' for item in fitems_p]
            for item, name, nameX in zip(fitems_p, fnames, fnamesX):
                outnames.append(rt.Make(name, item, '3', p_tag))
                outnames.append(rt.Make(nameX, item, '3X', p_tag))
        elif p == 'Pbar':
            p_tag = 'antiproton'
            fnames = [f'../table/{p}_{item}_y0p5.txt' for item in fitems_p]
            fnamesX = [f'../table/{p}_{item}_y0p5X.txt' for item in fitems_p]
            for item, name, nameX in zip(fitems_p, fnames, fnamesX):
                outnames.append(rt.Make(name, item, '3', p_tag))
                outnames.append(rt.Make(nameX, item, '3X', p_tag))

    if concate:
        with open(cat_name, 'w') as f:
            for subfile_name in outnames:
                for line in open(subfile_name):
                    f.writelines(line)
                f.write('\n\\clearpage\n')
