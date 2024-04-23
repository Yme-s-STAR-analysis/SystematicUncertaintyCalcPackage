r'''
    Table Caption Replace Scripts
    By Yige Huang
    07.02.2024
    Patch: 1.0
'''

class ReplaceTool:
    eng = "DATASET GeV"
    mapping = {
        "C1": r"$C_{1}$",
        "C2": r"$C_{2}$",
        "C3": r"$C_{3}$",
        "C4": r"$C_{4}$",
        "R21": r"$C_{2}$/$C_{1}$",
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

    def ReplaceCaption(self, cum_tag: str, withX: str):
        assert(cum_tag in self.mapping)
        assert(withX in ["3", "3X"])
        return f'\caption{{Detailed systematic uncertainty of net-proton {self.mapping[cum_tag]} from {self.eng} data set. Those systematic differences which did not pass Barlow check will be marked in red. $\Sigma$ is the systematic uncertainty from this source and the definition can be found in {self.eq_ref}. This table shows the results with centrality defined with RefMult{withX}.}}\n'
    
    def ReplaceLabel(self, cum_tag: str, withX: str):
        assert(cum_tag in self.mapping)
        assert(withX in ["3", "3X"])
        return f'\label{{tab:{cum_tag}_RefMult{withX}}}\n'
    
    def Make(self, fname: str, cum_tag: str, withX: str):
        # get the actual file name
        splits = fname.split('/')
        with open(fname, 'r') as f:
            l = f.readlines()
        fname = '/'.join(splits[:-1] + [f'Rep{splits[-1]}'])
        with open(fname, 'w') as f:
            for item in l:
                if item[1:8] == 'caption':
                    f.write(self.ReplaceCaption(cum_tag, withX))
                elif item[1:6] == 'label':
                    f.write(self.ReplaceLabel(cum_tag, withX))
                else:
                    f.write(item)
        return fname

# here is main
if __name__ == '__main__': 
    concate = True # if you want to get a looooong text file with all tables combined
    cat_name = '../tables/Concated.txt'
    rt = ReplaceTool()
    # ptypes = ['Netp', 'Pro', 'Pbar']
    ptypes = ['Netp']
    fitems = [
        'C1', 'C2', 'C3', 'C4', 'R21', 'R32', 'R42',
        # 'k1', 'k2', 'k3', 'k4', 'k21', 'k31', 'k41',
    ]
    outnames = []
    for p in ptypes:
        fnames = [f'../tables/{p}_{item}_y0p5.txt' for item in fitems if not (p == 'Netp' and item[0] == 'k')]
        fnamesX = [f'../tables/{p}_{item}_y0p5X.txt' for item in fitems if not (p == 'Netp' and item[0] == 'k')]
        for item, name, nameX in zip(fitems, fnames, fnamesX):
            outnames.append(rt.Make(name, item, '3'))
            outnames.append(rt.Make(nameX, item, '3X'))

    if concate:
        with open(cat_name, 'w') as f:
            for subfile_name in outnames:
                for line in open(subfile_name):
                    f.writelines(line)
                f.write('\n\n')
