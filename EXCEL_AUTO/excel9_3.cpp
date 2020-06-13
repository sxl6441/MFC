void Worksheets::Move(const VARIANT &Before, const VARIANT &After)
{
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x27d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                 &Before, &After);
}

LPUNKNOWN Worksheets::Get_NewEnum()
{
    LPUNKNOWN result;
    InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void *)&result, NULL);
    return result;
}

void Worksheets::PrintPreview(const VARIANT &EnableChanges)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x119, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                 &EnableChanges);
}

void Worksheets::Select(const VARIANT &Replace)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0xeb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                 &Replace);
}

LPDISPATCH Worksheets::GetHPageBreaks()
{
    LPDISPATCH result;
    InvokeHelper(0x58a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

LPDISPATCH Worksheets::GetVPageBreaks()
{
    LPDISPATCH result;
    InvokeHelper(0x58b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

VARIANT Worksheets::GetVisible()
{
    VARIANT result;
    InvokeHelper(0x22e, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Worksheets::SetVisible(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x22e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

LPDISPATCH Worksheets::Get_Default(const VARIANT &Index)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, parms,
                 &Index);
    return result;
}

void Worksheets::PrintOut(const VARIANT &From, const VARIANT &To, const VARIANT &Copies, const VARIANT &Preview,
                          const VARIANT &ActivePrinter, const VARIANT &PrintToFile, const VARIANT &Collate, const VARIANT &PrToFileName)
{
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x6ec, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                 &From, &To, &Copies, &Preview, &ActivePrinter, &PrintToFile, &Collate, &PrToFileName);
}

/////////////////////////////////////////////////////////////////////////////
// Range properties

/////////////////////////////////////////////////////////////////////////////
// Range operations

LPDISPATCH Range::GetApplication()
{
    LPDISPATCH result;
    InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

long Range::GetCreator()
{
    long result;
    InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void *)&result, NULL);
    return result;
}

LPDISPATCH Range::GetParent()
{
    LPDISPATCH result;
    InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

VARIANT Range::Activate()
{
    VARIANT result;
    InvokeHelper(0x130, DISPATCH_METHOD, VT_VARIANT, (void *)&result, NULL);
    return result;
}

VARIANT Range::GetAddIndent()
{
    VARIANT result;
    InvokeHelper(0x427, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetAddIndent(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x427, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

CString Range::GetAddress(const VARIANT &RowAbsolute, const VARIANT &ColumnAbsolute, long ReferenceStyle,
                          const VARIANT &External, const VARIANT &RelativeTo)
{
    CString result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT VTS_I4 VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0xec, DISPATCH_PROPERTYGET, VT_BSTR, (void *)&result, parms,
                 &RowAbsolute, &ColumnAbsolute, ReferenceStyle, &External, &RelativeTo);
    return result;
}

CString Range::GetAddressLocal(const VARIANT &RowAbsolute, const VARIANT &ColumnAbsolute, long ReferenceStyle,
                               const VARIANT &External, const VARIANT &RelativeTo)
{
    CString result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT VTS_I4 VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x1b5, DISPATCH_PROPERTYGET, VT_BSTR, (void *)&result, parms,
                 &RowAbsolute, &ColumnAbsolute, ReferenceStyle, &External, &RelativeTo);
    return result;
}

VARIANT Range::AdvancedFilter(long Action, const VARIANT &CriteriaRange, const VARIANT &CopyToRange,
                              const VARIANT &Unique)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x36c, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 Action, &CriteriaRange, &CopyToRange, &Unique);
    return result;
}

VARIANT Range::ApplyNames(const VARIANT &Names, const VARIANT &IgnoreRelativeAbsolute,
                          const VARIANT &UseRowColumnNames, const VARIANT &OmitColumn, const VARIANT &OmitRow, long Order,
                          const VARIANT &AppendLast)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_I4 VTS_VARIANT;
    InvokeHelper(0x1b9, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &Names, &IgnoreRelativeAbsolute, &UseRowColumnNames, &OmitColumn, &OmitRow, Order, &AppendLast);
    return result;
}

VARIANT Range::ApplyOutlineStyles()
{
    VARIANT result;
    InvokeHelper(0x1c0, DISPATCH_METHOD, VT_VARIANT, (void *)&result, NULL);
    return result;
}

LPDISPATCH Range::GetAreas()
{
    LPDISPATCH result;
    InvokeHelper(0x238, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

CString Range::AutoComplete(LPCTSTR String)
{
    CString result;
    static BYTE parms[] =
        VTS_BSTR;
    InvokeHelper(0x4a1, DISPATCH_METHOD, VT_BSTR, (void *)&result, parms,
                 String);
    return result;
}

VARIANT Range::AutoFill(LPDISPATCH Destination, long Type)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_DISPATCH VTS_I4;
    InvokeHelper(0x1c1, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 Destination, Type);
    return result;
}

VARIANT Range::AutoFilter(const VARIANT &Field, const VARIANT &Criteria1, long Operator, const VARIANT &Criteria2,
                          const VARIANT &VisibleDropDown)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT VTS_I4 VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x319, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &Field, &Criteria1, Operator, &Criteria2, &VisibleDropDown);
    return result;
}

VARIANT Range::AutoFit()
{
    VARIANT result;
    InvokeHelper(0xed, DISPATCH_METHOD, VT_VARIANT, (void *)&result, NULL);
    return result;
}

VARIANT Range::AutoFormat(long Format, const VARIANT &Number, const VARIANT &Font, const VARIANT &Alignment,
                          const VARIANT &Border, const VARIANT &Pattern, const VARIANT &Width)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x72, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 Format, &Number, &Font, &Alignment, &Border, &Pattern, &Width);
    return result;
}

VARIANT Range::AutoOutline()
{
    VARIANT result;
    InvokeHelper(0x40c, DISPATCH_METHOD, VT_VARIANT, (void *)&result, NULL);
    return result;
}

VARIANT Range::BorderAround(const VARIANT &LineStyle, long Weight, long ColorIndex, const VARIANT &Color)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT VTS_I4 VTS_I4 VTS_VARIANT;
    InvokeHelper(0x42b, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &LineStyle, Weight, ColorIndex, &Color);
    return result;
}

LPDISPATCH Range::GetBorders()
{
    LPDISPATCH result;
    InvokeHelper(0x1b3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

VARIANT Range::Calculate()
{
    VARIANT result;
    InvokeHelper(0x117, DISPATCH_METHOD, VT_VARIANT, (void *)&result, NULL);
    return result;
}

LPDISPATCH Range::GetCells()
{
    LPDISPATCH result;
    InvokeHelper(0xee, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

LPDISPATCH Range::GetCharacters(const VARIANT &Start, const VARIANT &Length)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x25b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, parms,
                 &Start, &Length);
    return result;
}

VARIANT Range::CheckSpelling(const VARIANT &CustomDictionary, const VARIANT &IgnoreUppercase,
                             const VARIANT &AlwaysSuggest, const VARIANT &SpellLang)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x1f9, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &CustomDictionary, &IgnoreUppercase, &AlwaysSuggest, &SpellLang);
    return result;
}

VARIANT Range::Clear()
{
    VARIANT result;
    InvokeHelper(0x6f, DISPATCH_METHOD, VT_VARIANT, (void *)&result, NULL);
    return result;
}

VARIANT Range::ClearContents()
{
    VARIANT result;
    InvokeHelper(0x71, DISPATCH_METHOD, VT_VARIANT, (void *)&result, NULL);
    return result;
}

VARIANT Range::ClearFormats()
{
    VARIANT result;
    InvokeHelper(0x70, DISPATCH_METHOD, VT_VARIANT, (void *)&result, NULL);
    return result;
}

VARIANT Range::ClearNotes()
{
    VARIANT result;
    InvokeHelper(0xef, DISPATCH_METHOD, VT_VARIANT, (void *)&result, NULL);
    return result;
}

VARIANT Range::ClearOutline()
{
    VARIANT result;
    InvokeHelper(0x40d, DISPATCH_METHOD, VT_VARIANT, (void *)&result, NULL);
    return result;
}

long Range::GetColumn()
{
    long result;
    InvokeHelper(0xf0, DISPATCH_PROPERTYGET, VT_I4, (void *)&result, NULL);
    return result;
}

LPDISPATCH Range::ColumnDifferences(const VARIANT &Comparison)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x1fe, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms,
                 &Comparison);
    return result;
}

LPDISPATCH Range::GetColumns()
{
    LPDISPATCH result;
    InvokeHelper(0xf1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

VARIANT Range::GetColumnWidth()
{
    VARIANT result;
    InvokeHelper(0xf2, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetColumnWidth(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0xf2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

VARIANT Range::Consolidate(const VARIANT &Sources, const VARIANT &Function, const VARIANT &TopRow,
                           const VARIANT &LeftColumn, const VARIANT &CreateLinks)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x1e2, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &Sources, &Function, &TopRow, &LeftColumn, &CreateLinks);
    return result;
}

VARIANT Range::Copy(const VARIANT &Destination)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x227, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &Destination);
    return result;
}

long Range::CopyFromRecordset(LPUNKNOWN Data, const VARIANT &MaxRows, const VARIANT &MaxColumns)
{
    long result;
    static BYTE parms[] =
        VTS_UNKNOWN VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x480, DISPATCH_METHOD, VT_I4, (void *)&result, parms,
                 Data, &MaxRows, &MaxColumns);
    return result;
}

VARIANT Range::CopyPicture(long Appearance, long Format)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_I4 VTS_I4;
    InvokeHelper(0xd5, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 Appearance, Format);
    return result;
}

long Range::GetCount()
{
    long result;
    InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_I4, (void *)&result, NULL);
    return result;
}

VARIANT Range::CreateNames(const VARIANT &Top, const VARIANT &Left, const VARIANT &Bottom, const VARIANT &Right)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x1c9, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &Top, &Left, &Bottom, &Right);
    return result;
}

VARIANT Range::CreatePublisher(const VARIANT &Edition, long Appearance, const VARIANT &ContainsPICT,
                               const VARIANT &ContainsBIFF, const VARIANT &ContainsRTF, const VARIANT &ContainsVALU)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x1ca, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &Edition, Appearance, &ContainsPICT, &ContainsBIFF, &ContainsRTF, &ContainsVALU);
    return result;
}

LPDISPATCH Range::GetCurrentArray()
{
    LPDISPATCH result;
    InvokeHelper(0x1f5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

LPDISPATCH Range::GetCurrentRegion()
{
    LPDISPATCH result;
    InvokeHelper(0xf3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

VARIANT Range::Cut(const VARIANT &Destination)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x235, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &Destination);
    return result;
}

VARIANT Range::DataSeries(const VARIANT &Rowcol, long Type, long Date, const VARIANT &Step, const VARIANT &Stop,
                          const VARIANT &Trend)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x1d0, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &Rowcol, Type, Date, &Step, &Stop, &Trend);
    return result;
}

VARIANT Range::Get_Default(const VARIANT &RowIndex, const VARIANT &ColumnIndex)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, parms,
                 &RowIndex, &ColumnIndex);
    return result;
}

void Range::Set_Default(const VARIANT &RowIndex, const VARIANT &ColumnIndex, const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &RowIndex, &ColumnIndex, &newValue);
}

VARIANT Range::Delete(const VARIANT &Shift)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x75, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &Shift);
    return result;
}

LPDISPATCH Range::GetDependents()
{
    LPDISPATCH result;
    InvokeHelper(0x21f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

VARIANT Range::DialogBox_()
{
    VARIANT result;
    InvokeHelper(0xf5, DISPATCH_METHOD, VT_VARIANT, (void *)&result, NULL);
    return result;
}

LPDISPATCH Range::GetDirectDependents()
{
    LPDISPATCH result;
    InvokeHelper(0x221, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

LPDISPATCH Range::GetDirectPrecedents()
{
    LPDISPATCH result;
    InvokeHelper(0x222, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

VARIANT Range::EditionOptions(long Type, long Option, const VARIANT &Name, const VARIANT &Reference,
                              long Appearance, long ChartSize, const VARIANT &Format)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT VTS_I4 VTS_I4 VTS_VARIANT;
    InvokeHelper(0x46b, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 Type, Option, &Name, &Reference, Appearance, ChartSize, &Format);
    return result;
}

LPDISPATCH Range::GetEnd(long Direction)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_I4;
    InvokeHelper(0x1f4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, parms,
                 Direction);
    return result;
}

LPDISPATCH Range::GetEntireColumn()
{
    LPDISPATCH result;
    InvokeHelper(0xf6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

LPDISPATCH Range::GetEntireRow()
{
    LPDISPATCH result;
    InvokeHelper(0xf7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

VARIANT Range::FillDown()
{
    VARIANT result;
    InvokeHelper(0xf8, DISPATCH_METHOD, VT_VARIANT, (void *)&result, NULL);
    return result;
}

VARIANT Range::FillLeft()
{
    VARIANT result;
    InvokeHelper(0xf9, DISPATCH_METHOD, VT_VARIANT, (void *)&result, NULL);
    return result;
}

VARIANT Range::FillRight()
{
    VARIANT result;
    InvokeHelper(0xfa, DISPATCH_METHOD, VT_VARIANT, (void *)&result, NULL);
    return result;
}

VARIANT Range::FillUp()
{
    VARIANT result;
    InvokeHelper(0xfb, DISPATCH_METHOD, VT_VARIANT, (void *)&result, NULL);
    return result;
}

LPDISPATCH Range::Find(const VARIANT &What, const VARIANT &After, const VARIANT &LookIn, const VARIANT &LookAt,
                       const VARIANT &SearchOrder, long SearchDirection, const VARIANT &MatchCase, const VARIANT &MatchByte)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_I4 VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x18e, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms,
                 &What, &After, &LookIn, &LookAt, &SearchOrder, SearchDirection, &MatchCase, &MatchByte);
    return result;
}

LPDISPATCH Range::FindNext(const VARIANT &After)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x18f, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms,
                 &After);
    return result;
}

LPDISPATCH Range::FindPrevious(const VARIANT &After)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x190, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms,
                 &After);
    return result;
}

LPDISPATCH Range::GetFont()
{
    LPDISPATCH result;
    InvokeHelper(0x92, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

VARIANT Range::GetFormula()
{
    VARIANT result;
    InvokeHelper(0x105, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetFormula(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x105, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

VARIANT Range::GetFormulaArray()
{
    VARIANT result;
    InvokeHelper(0x24a, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetFormulaArray(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x24a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

long Range::GetFormulaLabel()
{
    long result;
    InvokeHelper(0x564, DISPATCH_PROPERTYGET, VT_I4, (void *)&result, NULL);
    return result;
}

void Range::SetFormulaLabel(long nNewValue)
{
    static BYTE parms[] =
        VTS_I4;
    InvokeHelper(0x564, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 nNewValue);
}

VARIANT Range::GetFormulaHidden()
{
    VARIANT result;
    InvokeHelper(0x106, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetFormulaHidden(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x106, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

VARIANT Range::GetFormulaLocal()
{
    VARIANT result;
    InvokeHelper(0x107, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetFormulaLocal(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x107, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

VARIANT Range::GetFormulaR1C1()
{
    VARIANT result;
    InvokeHelper(0x108, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetFormulaR1C1(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x108, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

VARIANT Range::GetFormulaR1C1Local()
{
    VARIANT result;
    InvokeHelper(0x109, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetFormulaR1C1Local(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x109, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

VARIANT Range::FunctionWizard()
{
    VARIANT result;
    InvokeHelper(0x23b, DISPATCH_METHOD, VT_VARIANT, (void *)&result, NULL);
    return result;
}

BOOL Range::GoalSeek(const VARIANT &Goal, LPDISPATCH ChangingCell)
{
    BOOL result;
    static BYTE parms[] =
        VTS_VARIANT VTS_DISPATCH;
    InvokeHelper(0x1d8, DISPATCH_METHOD, VT_BOOL, (void *)&result, parms,
                 &Goal, ChangingCell);
    return result;
}

VARIANT Range::Group(const VARIANT &Start, const VARIANT &End, const VARIANT &By, const VARIANT &Periods)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x2e, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &Start, &End, &By, &Periods);
    return result;
}

VARIANT Range::GetHasArray()
{
    VARIANT result;
    InvokeHelper(0x10a, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

VARIANT Range::GetHasFormula()
{
    VARIANT result;
    InvokeHelper(0x10b, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

VARIANT Range::GetHeight()
{
    VARIANT result;
    InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

VARIANT Range::GetHidden()
{
    VARIANT result;
    InvokeHelper(0x10c, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetHidden(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x10c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

VARIANT Range::GetHorizontalAlignment()
{
    VARIANT result;
    InvokeHelper(0x88, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetHorizontalAlignment(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x88, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

VARIANT Range::GetIndentLevel()
{
    VARIANT result;
    InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetIndentLevel(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

void Range::InsertIndent(long InsertAmount)
{
    static BYTE parms[] =
        VTS_I4;
    InvokeHelper(0x565, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                 InsertAmount);
}

VARIANT Range::Insert(const VARIANT &Shift)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0xfc, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &Shift);
    return result;
}

LPDISPATCH Range::GetInterior()
{
    LPDISPATCH result;
    InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

VARIANT Range::GetItem(const VARIANT &RowIndex, const VARIANT &ColumnIndex)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0xaa, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, parms,
                 &RowIndex, &ColumnIndex);
    return result;
}

void Range::SetItem(const VARIANT &RowIndex, const VARIANT &ColumnIndex, const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0xaa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &RowIndex, &ColumnIndex, &newValue);
}

VARIANT Range::Justify()
{
    VARIANT result;
    InvokeHelper(0x1ef, DISPATCH_METHOD, VT_VARIANT, (void *)&result, NULL);
    return result;
}

VARIANT Range::GetLeft()
{
    VARIANT result;
    InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

long Range::GetListHeaderRows()
{
    long result;
    InvokeHelper(0x4a3, DISPATCH_PROPERTYGET, VT_I4, (void *)&result, NULL);
    return result;
}

VARIANT Range::ListNames()
{
    VARIANT result;
    InvokeHelper(0xfd, DISPATCH_METHOD, VT_VARIANT, (void *)&result, NULL);
    return result;
}

long Range::GetLocationInTable()
{
    long result;
    InvokeHelper(0x2b3, DISPATCH_PROPERTYGET, VT_I4, (void *)&result, NULL);
    return result;
}

VARIANT Range::GetLocked()
{
    VARIANT result;
    InvokeHelper(0x10d, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetLocked(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x10d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

void Range::Merge(const VARIANT &Across)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x234, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                 &Across);
}

void Range::UnMerge()
{
    InvokeHelper(0x568, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Range::GetMergeArea()
{
    LPDISPATCH result;
    InvokeHelper(0x569, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

VARIANT Range::GetMergeCells()
{
    VARIANT result;
    InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetMergeCells(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0xd0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

VARIANT Range::GetName()
{
    VARIANT result;
    InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetName(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x6e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

VARIANT Range::NavigateArrow(const VARIANT &TowardPrecedent, const VARIANT &ArrowNumber, const VARIANT &LinkNumber)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x408, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &TowardPrecedent, &ArrowNumber, &LinkNumber);
    return result;
}

LPUNKNOWN Range::Get_NewEnum()
{
    LPUNKNOWN result;
    InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void *)&result, NULL);
    return result;
}

LPDISPATCH Range::GetNext()
{
    LPDISPATCH result;
    InvokeHelper(0x1f6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

CString Range::NoteText(const VARIANT &Text, const VARIANT &Start, const VARIANT &Length)
{
    CString result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x467, DISPATCH_METHOD, VT_BSTR, (void *)&result, parms,
                 &Text, &Start, &Length);
    return result;
}

VARIANT Range::GetNumberFormat()
{
    VARIANT result;
    InvokeHelper(0xc1, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetNumberFormat(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0xc1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

VARIANT Range::GetNumberFormatLocal()
{
    VARIANT result;
    InvokeHelper(0x449, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetNumberFormatLocal(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x449, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

LPDISPATCH Range::GetOffset(const VARIANT &RowOffset, const VARIANT &ColumnOffset)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0xfe, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, parms,
                 &RowOffset, &ColumnOffset);
    return result;
}

VARIANT Range::GetOrientation()
{
    VARIANT result;
    InvokeHelper(0x86, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetOrientation(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x86, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

VARIANT Range::GetOutlineLevel()
{
    VARIANT result;
    InvokeHelper(0x10f, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetOutlineLevel(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x10f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

long Range::GetPageBreak()
{
    long result;
    InvokeHelper(0xff, DISPATCH_PROPERTYGET, VT_I4, (void *)&result, NULL);
    return result;
}

void Range::SetPageBreak(long nNewValue)
{
    static BYTE parms[] =
        VTS_I4;
    InvokeHelper(0xff, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 nNewValue);
}

VARIANT Range::Parse(const VARIANT &ParseLine, const VARIANT &Destination)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x1dd, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &ParseLine, &Destination);
    return result;
}

VARIANT Range::PasteSpecial(long Paste, long Operation, const VARIANT &SkipBlanks, const VARIANT &Transpose)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x403, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 Paste, Operation, &SkipBlanks, &Transpose);
    return result;
}

LPDISPATCH Range::GetPivotField()
{
    LPDISPATCH result;
    InvokeHelper(0x2db, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

LPDISPATCH Range::GetPivotItem()
{
    LPDISPATCH result;
    InvokeHelper(0x2e4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

LPDISPATCH Range::GetPivotTable()
{
    LPDISPATCH result;
    InvokeHelper(0x2cc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

LPDISPATCH Range::GetPrecedents()
{
    LPDISPATCH result;
    InvokeHelper(0x220, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

VARIANT Range::GetPrefixCharacter()
{
    VARIANT result;
    InvokeHelper(0x1f8, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

LPDISPATCH Range::GetPrevious()
{
    LPDISPATCH result;
    InvokeHelper(0x1f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

VARIANT Range::_PrintOut(const VARIANT &From, const VARIANT &To, const VARIANT &Copies, const VARIANT &Preview,
                         const VARIANT &ActivePrinter, const VARIANT &PrintToFile, const VARIANT &Collate)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x389, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &From, &To, &Copies, &Preview, &ActivePrinter, &PrintToFile, &Collate);
    return result;
}

VARIANT Range::PrintPreview(const VARIANT &EnableChanges)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x119, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &EnableChanges);
    return result;
}

LPDISPATCH Range::GetQueryTable()
{
    LPDISPATCH result;
    InvokeHelper(0x56a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

LPDISPATCH Range::GetRange(const VARIANT &Cell1, const VARIANT &Cell2)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0xc5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, parms,
                 &Cell1, &Cell2);
    return result;
}

VARIANT Range::RemoveSubtotal()
{
    VARIANT result;
    InvokeHelper(0x373, DISPATCH_METHOD, VT_VARIANT, (void *)&result, NULL);
    return result;
}

BOOL Range::Replace(const VARIANT &What, const VARIANT &Replacement, const VARIANT &LookAt,
                    const VARIANT &SearchOrder, const VARIANT &MatchCase, const VARIANT &MatchByte)
{
    BOOL result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0xe2, DISPATCH_METHOD, VT_BOOL, (void *)&result, parms,
                 &What, &Replacement, &LookAt, &SearchOrder, &MatchCase, &MatchByte);
    return result;
}

LPDISPATCH Range::GetResize(const VARIANT &RowSize, const VARIANT &ColumnSize)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x100, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, parms,
                 &RowSize, &ColumnSize);
    return result;
}

long Range::GetRow()
{
    long result;
    InvokeHelper(0x101, DISPATCH_PROPERTYGET, VT_I4, (void *)&result, NULL);
    return result;
}

LPDISPATCH Range::RowDifferences(const VARIANT &Comparison)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x1ff, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms,
                 &Comparison);
    return result;
}

VARIANT Range::GetRowHeight()
{
    VARIANT result;
    InvokeHelper(0x110, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetRowHeight(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x110, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

LPDISPATCH Range::GetRows()
{
    LPDISPATCH result;
    InvokeHelper(0x102, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

VARIANT Range::Run(const VARIANT &Arg1, const VARIANT &Arg2, const VARIANT &Arg3, const VARIANT &Arg4,
                   const VARIANT &Arg5, const VARIANT &Arg6, const VARIANT &Arg7, const VARIANT &Arg8, const VARIANT &Arg9,
                   const VARIANT &Arg10,
                   const VARIANT &Arg11, const VARIANT &Arg12, const VARIANT &Arg13, const VARIANT &Arg14, const VARIANT &Arg15,
                   const VARIANT &Arg16, const VARIANT &Arg17, const VARIANT &Arg18, const VARIANT &Arg19, const VARIANT &Arg20,
                   const VARIANT &Arg21, const VARIANT &Arg22, const VARIANT &Arg23, const VARIANT &Arg24, const VARIANT &Arg25,
                   const VARIANT &Arg26, const VARIANT &Arg27, const VARIANT &Arg28, const VARIANT &Arg29, const VARIANT &Arg30)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT
        VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT
        VTS_VARIANT
        VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT
        VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x103, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15,
                 &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29,
                 &Arg30);
    return result;
}

VARIANT Range::Select()
{
    VARIANT result;
    InvokeHelper(0xeb, DISPATCH_METHOD, VT_VARIANT, (void *)&result, NULL);
    return result;
}

VARIANT Range::Show()
{
    VARIANT result;
    InvokeHelper(0x1f0, DISPATCH_METHOD, VT_VARIANT, (void *)&result, NULL);
    return result;
}

VARIANT Range::ShowDependents(const VARIANT &Remove)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x36d, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &Remove);
    return result;
}

VARIANT Range::GetShowDetail()
{
    VARIANT result;
    InvokeHelper(0x249, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetShowDetail(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x249, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

VARIANT Range::ShowErrors()
{
    VARIANT result;
    InvokeHelper(0x36e, DISPATCH_METHOD, VT_VARIANT, (void *)&result, NULL);
    return result;
}

VARIANT Range::ShowPrecedents(const VARIANT &Remove)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x36f, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &Remove);
    return result;
}

VARIANT Range::GetShrinkToFit()
{
    VARIANT result;
    InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetShrinkToFit(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0xd1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

VARIANT Range::Sort(const VARIANT &Key1, long Order1, const VARIANT &Key2, const VARIANT &Type, long Order2,
                    const VARIANT &Key3, long Order3, long Header, const VARIANT &OrderCustom, const VARIANT &MatchCase,
                    long Orientation, long SortMethod)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT VTS_I4 VTS_VARIANT VTS_VARIANT VTS_I4 VTS_VARIANT VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT VTS_I4 VTS_I4;
    InvokeHelper(0x370, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &Key1, Order1, &Key2, &Type, Order2, &Key3, Order3, Header, &OrderCustom, &MatchCase, Orientation, SortMethod);
    return result;
}

VARIANT Range::SortSpecial(long SortMethod, const VARIANT &Key1, long Order1, const VARIANT &Type,
                           const VARIANT &Key2, long Order2, const VARIANT &Key3, long Order3, long Header, const VARIANT &OrderCustom,
                           const VARIANT &MatchCase,
                           long Orientation)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_I4 VTS_VARIANT VTS_I4 VTS_VARIANT VTS_VARIANT VTS_I4 VTS_VARIANT VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT VTS_I4;
    InvokeHelper(0x371, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 SortMethod, &Key1, Order1, &Type, &Key2, Order2, &Key3, Order3, Header, &OrderCustom, &MatchCase, Orientation);
    return result;
}

LPDISPATCH Range::GetSoundNote()
{
    LPDISPATCH result;
    InvokeHelper(0x394, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

LPDISPATCH Range::SpecialCells(long Type, const VARIANT &Value)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_I4 VTS_VARIANT;
    InvokeHelper(0x19a, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms,
                 Type, &Value);
    return result;
}

VARIANT Range::GetStyle()
{
    VARIANT result;
    InvokeHelper(0x104, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetStyle(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x104, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

VARIANT Range::SubscribeTo(LPCTSTR Edition, long Format)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_BSTR VTS_I4;
    InvokeHelper(0x1e1, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 Edition, Format);
    return result;
}

VARIANT Range::Subtotal(long GroupBy, long Function, const VARIANT &TotalList, const VARIANT &Replace,
                        const VARIANT &PageBreaks, long SummaryBelowData)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_I4;
    InvokeHelper(0x372, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 GroupBy, Function, &TotalList, &Replace, &PageBreaks, SummaryBelowData);
    return result;
}

VARIANT Range::GetSummary()
{
    VARIANT result;
    InvokeHelper(0x111, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

VARIANT Range::Table(const VARIANT &RowInput, const VARIANT &ColumnInput)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x1f1, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &RowInput, &ColumnInput);
    return result;
}

VARIANT Range::GetText()
{
    VARIANT result;
    InvokeHelper(0x8a, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

VARIANT Range::TextToColumns(const VARIANT &Destination, long DataType, long TextQualifier,
                             const VARIANT &ConsecutiveDelimiter, const VARIANT &Tab, const VARIANT &Semicolon, const VARIANT &Comma,
                             const VARIANT &Space, const VARIANT &Other,
                             const VARIANT &OtherChar, const VARIANT &FieldInfo, const VARIANT &DecimalSeparator,
                             const VARIANT &ThousandsSeparator)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT
        VTS_VARIANT VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x410, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &Destination, DataType, TextQualifier, &ConsecutiveDelimiter, &Tab, &Semicolon, &Comma, &Space, &Other, &OtherChar,
                 &FieldInfo, &DecimalSeparator, &ThousandsSeparator);
    return result;
}

VARIANT Range::GetTop()
{
    VARIANT result;
    InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

VARIANT Range::Ungroup()
{
    VARIANT result;
    InvokeHelper(0xf4, DISPATCH_METHOD, VT_VARIANT, (void *)&result, NULL);
    return result;
}

VARIANT Range::GetUseStandardHeight()
{
    VARIANT result;
    InvokeHelper(0x112, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetUseStandardHeight(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x112, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

VARIANT Range::GetUseStandardWidth()
{
    VARIANT result;
    InvokeHelper(0x113, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetUseStandardWidth(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x113, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

LPDISPATCH Range::GetValidation()
{
    LPDISPATCH result;
    InvokeHelper(0x56b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

VARIANT Range::GetValue()
{
    VARIANT result;
    InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetValue(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

VARIANT Range::GetValue2()
{
    VARIANT result;
    InvokeHelper(0x56c, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetValue2(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x56c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

VARIANT Range::GetVerticalAlignment()
{
    VARIANT result;
    InvokeHelper(0x89, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetVerticalAlignment(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x89, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

VARIANT Range::GetWidth()
{
    VARIANT result;
    InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

LPDISPATCH Range::GetWorksheet()
{
    LPDISPATCH result;
    InvokeHelper(0x15c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

VARIANT Range::GetWrapText()
{
    VARIANT result;
    InvokeHelper(0x114, DISPATCH_PROPERTYGET, VT_VARIANT, (void *)&result, NULL);
    return result;
}

void Range::SetWrapText(const VARIANT &newValue)
{
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x114, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 &newValue);
}

LPDISPATCH Range::AddComment(const VARIANT &Text)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x56d, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms,
                 &Text);
    return result;
}

LPDISPATCH Range::GetComment()
{
    LPDISPATCH result;
    InvokeHelper(0x38e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

void Range::ClearComments()
{
    InvokeHelper(0x56e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Range::GetPhonetic()
{
    LPDISPATCH result;
    InvokeHelper(0x56f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

LPDISPATCH Range::GetFormatConditions()
{
    LPDISPATCH result;
    InvokeHelper(0x570, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

long Range::GetReadingOrder()
{
    long result;
    InvokeHelper(0x3cf, DISPATCH_PROPERTYGET, VT_I4, (void *)&result, NULL);
    return result;
}

void Range::SetReadingOrder(long nNewValue)
{
    static BYTE parms[] =
        VTS_I4;
    InvokeHelper(0x3cf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 nNewValue);
}

LPDISPATCH Range::GetHyperlinks()
{
    LPDISPATCH result;
    InvokeHelper(0x571, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

LPDISPATCH Range::GetPhonetics()
{
    LPDISPATCH result;
    InvokeHelper(0x713, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

void Range::SetPhonetic()
{
    InvokeHelper(0x714, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString Range::GetId()
{
    CString result;
    InvokeHelper(0x715, DISPATCH_PROPERTYGET, VT_BSTR, (void *)&result, NULL);
    return result;
}

void Range::SetId(LPCTSTR lpszNewValue)
{
    static BYTE parms[] =
        VTS_BSTR;
    InvokeHelper(0x715, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                 lpszNewValue);
}

VARIANT Range::PrintOut(const VARIANT &From, const VARIANT &To, const VARIANT &Copies, const VARIANT &Preview,
                        const VARIANT &ActivePrinter, const VARIANT &PrintToFile, const VARIANT &Collate, const VARIANT &PrToFileName)
{
    VARIANT result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x6ec, DISPATCH_METHOD, VT_VARIANT, (void *)&result, parms,
                 &From, &To, &Copies, &Preview, &ActivePrinter, &PrintToFile, &Collate, &PrToFileName);
    return result;
}

/////////////////////////////////////////////////////////////////////////////
// Shapes properties

/////////////////////////////////////////////////////////////////////////////
// Shapes operations

LPDISPATCH Shapes::GetApplication()
{
    LPDISPATCH result;
    InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

long Shapes::GetCreator()
{
    long result;
    InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void *)&result, NULL);
    return result;
}

LPDISPATCH Shapes::GetParent()
{
    LPDISPATCH result;
    InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, NULL);
    return result;
}

long Shapes::GetCount()
{
    long result;
    InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_I4, (void *)&result, NULL);
    return result;
}

LPDISPATCH Shapes::Item(const VARIANT &Index)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0xaa, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms,
                 &Index);
    return result;
}

LPDISPATCH Shapes::_Default(const VARIANT &Index)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms,
                 &Index);
    return result;
}

LPUNKNOWN Shapes::Get_NewEnum()
{
    LPUNKNOWN result;
    InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void *)&result, NULL);
    return result;
}

LPDISPATCH Shapes::AddCallout(long Type, float Left, float Top, float Width, float Height)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
    InvokeHelper(0x6b1, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms,
                 Type, Left, Top, Width, Height);
    return result;
}

LPDISPATCH Shapes::AddConnector(long Type, float BeginX, float BeginY, float EndX, float EndY)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
    InvokeHelper(0x6b2, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms,
                 Type, BeginX, BeginY, EndX, EndY);
    return result;
}

LPDISPATCH Shapes::AddCurve(const VARIANT &SafeArrayOfPoints)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x6b7, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms,
                 &SafeArrayOfPoints);
    return result;
}

LPDISPATCH Shapes::AddLabel(long Orientation, float Left, float Top, float Width, float Height)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
    InvokeHelper(0x6b9, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms,
                 Orientation, Left, Top, Width, Height);
    return result;
}

LPDISPATCH Shapes::AddLine(float BeginX, float BeginY, float EndX, float EndY)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_R4 VTS_R4 VTS_R4 VTS_R4;
    InvokeHelper(0x6ba, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms,
                 BeginX, BeginY, EndX, EndY);
    return result;
}

LPDISPATCH Shapes::AddPicture(LPCTSTR Filename, long LinkToFile, long SaveWithDocument, float Left, float Top,
                              float Width, float Height)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_BSTR VTS_I4 VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
    InvokeHelper(0x6bb, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms,
                 Filename, LinkToFile, SaveWithDocument, Left, Top, Width, Height);
    return result;
}

LPDISPATCH Shapes::AddPolyline(const VARIANT &SafeArrayOfPoints)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0x6be, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms,
                 &SafeArrayOfPoints);
    return result;
}

LPDISPATCH Shapes::AddShape(long Type, float Left, float Top, float Width, float Height)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
    InvokeHelper(0x6bf, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms,
                 Type, Left, Top, Width, Height);
    return result;
}

LPDISPATCH Shapes::AddTextEffect(long PresetTextEffect, LPCTSTR Text, LPCTSTR FontName, float FontSize,
                                 long FontBold, long FontItalic, float Left, float Top)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_I4 VTS_BSTR VTS_BSTR VTS_R4 VTS_I4 VTS_I4 VTS_R4 VTS_R4;
    InvokeHelper(0x6c0, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms,
                 PresetTextEffect, Text, FontName, FontSize, FontBold, FontItalic, Left, Top);
    return result;
}

LPDISPATCH Shapes::AddTextbox(long Orientation, float Left, float Top, float Width, float Height)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4;
    InvokeHelper(0x6c6, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms,
                 Orientation, Left, Top, Width, Height);
    return result;
}

LPDISPATCH Shapes::BuildFreeform(long EditingType, float X1, float Y1)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_I4 VTS_R4 VTS_R4;
    InvokeHelper(0x6c7, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms,
                 EditingType, X1, Y1);
    return result;
}

LPDISPATCH Shapes::GetRange(const VARIANT &Index)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_VARIANT;
    InvokeHelper(0xc5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&result, parms,
                 &Index);
    return result;
}

void Shapes::SelectAll()
{
    InvokeHelper(0x6c9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Shapes::AddFormControl(long Type, long Left, long Top, long Width, long Height)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
    InvokeHelper(0x6ca, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms,
                 Type, Left, Top, Width, Height);
    return result;
}

LPDISPATCH Shapes::AddOLEObject(const VARIANT &ClassType, const VARIANT &Filename, const VARIANT &Link,
                                const VARIANT &DisplayAsIcon, const VARIANT &IconFileName, const VARIANT &IconIndex, const VARIANT &IconLabel,
                                const VARIANT &Left,
                                const VARIANT &Top, const VARIANT &Width, const VARIANT &Height)
{
    LPDISPATCH result;
    static BYTE parms[] =
        VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT
        VTS_VARIANT VTS_VARIANT;
    InvokeHelper(0x6cb, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms,
                 &ClassType, &Filename, &Link, &DisplayAsIcon, &IconFileName, &IconIndex, &IconLabel, &Left, &Top, &Width, &Height);
    return result;
}
