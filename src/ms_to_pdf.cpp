/*
 * This file is part of openpdfguard.
 * Copyright (C) 2025 Samuil Ivanov
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; If not, see <http://www.gnu.org/licenses/>.
 *
 * This file uses interfaces from the LibreOffice UNO API,
 * licensed under the Mozilla Public License v2.0.
 * See: https://www.mozilla.org/MPL/2.0/
 *
 */

#include "ms_to_pdf.h"

#include <osl/process.h>
#include <podofo/podofo.h>
#include <rtl/process.h>
#include <sal/main.h>

#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/bridge/XUnoUrlResolver.hpp>
#include <com/sun/star/frame/Desktop.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/frame/XStorable.hpp>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <com/sun/star/text/XTextDocument.hpp>
#include <cppuhelper/bootstrap.hxx>
#include <iostream>
#include <osl/file.hxx>
#include <rtl/bootstrap.hxx>

#include "rtl/ustring.h"
#include "rtl/ustring.hxx"
#include "sal/types.h"

using namespace cppu;
using namespace rtl;
using namespace css::uno;
using namespace css::beans;
using namespace css::bridge;
using namespace css::frame;
using namespace css::lang;
using namespace css::text;

namespace opg {

void ms_to_pdf::convert(std::string_view input, std::string_view output) {
  // TODO(samuil): this should be refactored not ok to have this hardcoded thing
  // here
  ::setenv("URE_MORE_TYPES",
           "file:///usr/lib/libreoffice/program/types/offapi.rdb", 1);

  OUString sConnectionString(
      "uno:socket,host=localhost,port=2083;urp;StarOffice.ServiceManager");

  Reference<XComponentContext> xComponentContext(
      defaultBootstrap_InitialComponentContext());
  Reference<XMultiComponentFactory> xMultiComponentFactoryClient(
      xComponentContext->getServiceManager());
  Reference<XInterface> xInterface =
      xMultiComponentFactoryClient->createInstanceWithContext(
          "com.sun.star.bridge.UnoUrlResolver", xComponentContext);
  Reference<XUnoUrlResolver> resolver(xInterface, UNO_QUERY);
  try {
    xInterface = Reference<XInterface>(resolver->resolve(sConnectionString),
                                       UNO_QUERY_THROW);
  } catch (Exception& e) {
    std::cout << "Error: cannot establish a connection using '"
              << sConnectionString << "'" << std::endl
              << e.Message << std::endl;
    std::exit(1);
  }

  Reference<XPropertySet> xPropSet(xInterface, UNO_QUERY);
  xPropSet->getPropertyValue("DefaultContext") >>= xComponentContext;
  Reference<XMultiComponentFactory> xMultiComponentFactoryServer(
      xComponentContext->getServiceManager());
  Reference<XDesktop2> xComponentLoader = Desktop::create(xComponentContext);
  Sequence<PropertyValue> loadProperties(1);
  loadProperties[0].Name = "Hidden";
  loadProperties[0].Value <<= true;
  try {
    OUString sInputUrl, sAbsoluteInputUrl, sOutputUrl, sAbsoluteOutputUrl,
        sWorkingDir;
    osl_getProcessWorkingDir(&sWorkingDir.pData);
    OUString sInputFileName = OUString::createFromAscii(input.data());
    osl::FileBase::getFileURLFromSystemPath(sInputFileName, sInputUrl);
    osl::FileBase::getAbsoluteFileURL(sWorkingDir, sInputUrl,
                                      sAbsoluteInputUrl);
    std::cout << sAbsoluteInputUrl << std::endl;
    OUString sOutputFileName = OUString::createFromAscii(output.data());

    osl::FileBase::getFileURLFromSystemPath(sOutputFileName, sOutputUrl);
    osl::FileBase::getAbsoluteFileURL(sWorkingDir, sOutputUrl,
                                      sAbsoluteOutputUrl);
    std::cout << sAbsoluteOutputUrl << std::endl;

    Reference<XComponent> xComponent = xComponentLoader->loadComponentFromURL(
        sAbsoluteInputUrl, "_blank", 0, loadProperties);
    Reference<XTextDocument> xDocument(xComponent, UNO_QUERY_THROW);
    Reference<XStorable> xStorable(xDocument, UNO_QUERY_THROW);
    Sequence<PropertyValue> storeProps(3);
    storeProps[0].Name = "FilterName";
    storeProps[0].Value <<= OUString("writer_pdf_Export");
    storeProps[1].Name = "Overwrite";
    storeProps[1].Value <<= true;
    storeProps[2].Name = "SelectPdfVersion";
    storeProps[2].Value <<= sal_Int32(1);
    xStorable->storeToURL(sAbsoluteOutputUrl, storeProps);
    Reference<XComponent>::query(xMultiComponentFactoryClient)->dispose();
    std::cout << "Output output.pdf generated." << std::endl;
  } catch (Exception& e) {
    std::cout << "Can not open the input file." << std::endl
              << e.Message << std::endl;
  }
}
}  // namespace opg